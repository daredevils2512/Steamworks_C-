#include "Robot.h"
#include "Commands/AutoTimedDriveForward.h"
#include <Encoder.h>
#include "Commands/_CMG_AutonomousGearFarPeg.h"
#include "Commands/_CMG_AutonomousGearCenterPeg.h"
#include "Commands/_CMG_AutonomousGearClosePeg.h"
#include "Commands/_CMG_AutonomousHopper.h"

//access pointer objects declared in Robot.h
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<FloorIntake> Robot::floorIntake;
std::shared_ptr<Gear> Robot::gear;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<PixySubsystem> Robot::pixySubsystem;
std::unique_ptr<OI> Robot::oi;
frc::DriverStation::Alliance Robot::robotAlliance;

std::shared_ptr<frc::Compressor> Robot::compressor;

void Robot::RobotInit() {
	//starts subsystems and creates new instances of them
	RobotMap::init();
    drivetrain.reset(new Drivetrain());
    climber.reset(new Climber());
    floorIntake.reset(new FloorIntake());
    gear.reset(new Gear());
    shooter.reset(new Shooter());
    pixySubsystem.reset(new PixySubsystem());

    //starts operator interface
	oi.reset(new OI());

	compressor.reset(new frc::Compressor());
//	frc::CameraServer::GetInstance()->StartAutomaticCapture(); //this should be running, commented out for testing
//	frc::CameraServer::GetInstance()->StartAutomaticCapture();
  }

void Robot::DisabledInit(){
	compressor->SetClosedLoopControl(false);
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	//starts autonomous
	Robot::robotAlliance = frc::DriverStation::GetInstance().GetAlliance();

	Robot::shooter->SetFlywheelSpeed(0.0);
	Robot::shooter->SetSpinCycleFeedSpeed(0.0);
	Robot::floorIntake->SetSpeed(0.0);
	Robot::shooter->SetSwivelSpeed(0.0);
	Robot::drivetrain->SetAutonomous(true);
	Robot::drivetrain->ResetEncoders();
	std::ifstream ifs("/home/lvuser/Autonomous.txt");
	if(!ifs.good()) {
		std::cout << "ERROR: no auto file" << std::endl;
		ifs.close();
		return;
	}
	while (!ifs.eof()) {
		std::string firstPart;
		std::string lastPart;
		std::getline(ifs, firstPart, ':');
		std::getline(ifs, lastPart);
		while(lastPart[0] == ' '){
			lastPart = lastPart.substr(1);
		}
		if(!ifs.eof()){
			lastPart = lastPart.substr(0,lastPart.size()-1);
		}
		if (firstPart == "Autonomous") {
			if (lastPart == "Far") {
				autonomousCommand.reset(new _CMG_AutonomousGearFarPeg());
				std::cout << "far" << std::endl;
			} else if (lastPart == "Close") {
				autonomousCommand.reset(new _CMG_AutonomousGearClosePeg(false));
				std::cout << "close" << std::endl;
			} else if (lastPart == "Center") {
				autonomousCommand.reset(new _CMG_AutonomousGearCenterPeg());
				std::cout << "center" << std::endl;
			} else if (lastPart == "Hopper") {
				autonomousCommand.reset(new _CMG_AutonomousHopper());
				std::cout << "just hopper" << std::endl;
			}
		} else if (firstPart == "DoHopper") {
			if (lastPart == "Yes") {
				autonomousCommand.reset(new _CMG_AutonomousGearClosePeg(true));
				std::cout << "close with hopper" << std::endl;
			} else if (lastPart == "No") {
				autonomousCommand.reset(new _CMG_AutonomousGearClosePeg(false));
				std::cout << "close without hopper" << std::endl;
			}

		}
	}
	ifs.close();
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	SmartDashboard::PutNumber("left encoder", RobotMap::drivetrainLeftEncoder->GetDistance());
	SmartDashboard::PutNumber("right encoder", RobotMap::drivetrainRightEncoder->GetDistance());
}

void Robot::TeleopInit() {
	//stops autonomous command
	Robot::shooter->SetFlywheelSpeed(0.0);
	Robot::shooter->SetSpinCycleFeedSpeed(0.0);
	Robot::floorIntake->SetSpeed(0.0);
	Robot::shooter->SetSwivelSpeed(0.0);
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
	Robot::drivetrain->SetAutonomous(false);
	compressor->SetClosedLoopControl(true);
	Robot::shooter->SetSwivelSpeed(0.0);
	Robot::drivetrain->ResetEncoders();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	//prints information to the smart dashboard
	SmartDashboard::PutNumber("swivel encoder", RobotMap::shooterTurretSwivel->GetEncPosition());
	SmartDashboard::PutNumber("left flywheel speed", RobotMap::shooterFlywheel->GetSpeed());
	SmartDashboard::PutNumber("fly setpoint", RobotMap::shooterFlywheel->Get());
	SmartDashboard::PutBoolean("gear limit switch" , Robot::gear->GetLimitSwitch());
	SmartDashboard::PutNumber("left encoder", RobotMap::drivetrainLeftEncoder->GetDistance());
//	SmartDashboard::PutBoolean("left encoder digitalcheck", RobotMap::drivetrainLeftEncoder->CheckDigitalChannel(2));
	SmartDashboard::PutNumber("right encoder", RobotMap::drivetrainRightEncoder->GetDistance());
//	SmartDashboard::PutBoolean("right encoder digitalcheck", RobotMap::drivetrainRightEncoder->CheckDigitalChannel(4));
	SmartDashboard::PutNumber("subsystem get left encoder", Robot::drivetrain->GetLeftEncoder());
	SmartDashboard::PutNumber("subsystem get right encoder", Robot::drivetrain->GetRightEncoder());
	SmartDashboard::PutNumber("left encoder raw", RobotMap::drivetrainLeftEncoder->Get());
	SmartDashboard::PutNumber("right encoder raw", RobotMap::drivetrainRightEncoder->Get());
	SmartDashboard::PutBoolean("gear release switch", Robot::gear->GetReleaseLimitSwitch());
	SmartDashboard::PutNumber("flywheel RPM", RobotMap::shooterFlywheel->GetSpeed());
}

void Robot::TestPeriodic() {
	//lw->Run();
}

START_ROBOT_CLASS(Robot);
