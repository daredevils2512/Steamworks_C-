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
	frc::CameraServer::GetInstance()->StartAutomaticCapture();
	frc::CameraServer::GetInstance()->StartAutomaticCapture();
  }

void Robot::DisabledInit(){
	compressor->SetClosedLoopControl(false);
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	//starts autonomous
	Robot::shooter->SetFlywheelSpeed(0.0);
	Robot::shooter->SetSpinCycleFeedSpeed(0.0);
	Robot::floorIntake->SetSpeed(0.0);
	Robot::shooter->SetSwivelSpeed(0.0);
	Robot::drivetrain->SetAutonomous(true);
//	autonomousCommand.reset(new _CMG_AutonomousGearFarPeg());
//	autonomousCommand.reset(new _CMG_AutonomousGearCenterPeg());
	autonomousCommand.reset(new _CMG_AutonomousGearClosePeg(true));
//	autonomousCommand.reset(new _CMG_AutonomousHopper());
	std::ifstream ifs("C:\\Users\\daredevils\\Desktop\\FileIO test file.txt"); // TODO: this wont work so fix it, use local filesystem on roborio
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
			} else if (lastPart == "Close") {
				autonomousCommand.reset(new _CMG_AutonomousGearClosePeg(false));
			} else if (lastPart == "Center") {
				autonomousCommand.reset(new _CMG_AutonomousGearCenterPeg());
			} else if (lastPart == "Hopper") {
				autonomousCommand.reset(new _CMG_AutonomousHopper());
			}
		} else if (firstPart == "DoHopper") {
			if (lastPart == "Yes") {
				autonomousCommand.reset(new _CMG_AutonomousGearClosePeg(true));
			} else if (lastPart == "No") {
				autonomousCommand.reset(new _CMG_AutonomousGearClosePeg(false));
			}

		}
	}
	ifs.close();
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
//	gear->UpdateGearActuator();
//	Scheduler::GetInstance()->RemoveAll();
	Scheduler::GetInstance()->Run();
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
	//gear->UpdateGearActuator();
	Scheduler::GetInstance()->Run();
	//prints information to the smart dashboard
	SmartDashboard::PutNumber("left encoder" , RobotMap::drivetrainLeftEncoder->GetDistance());
	SmartDashboard::PutNumber("right encoder", RobotMap::drivetrainRightEncoder->GetDistance());
	SmartDashboard::PutBoolean("encoder left test", RobotMap::drivetrainLeftEncoder->GetStopped());
	SmartDashboard::PutNumber("left encoder distance", Robot::drivetrain->GetLeftEncoder());
	SmartDashboard::PutNumber("right encoder distance", Robot::drivetrain->GetRightEncoder());
	SmartDashboard::PutNumber("swivel encoder", RobotMap::shooterTurretSwivel->GetEncPosition());
	SmartDashboard::PutNumber("left flywheel speed", RobotMap::shooterLeftFlywheel->GetSpeed());
	SmartDashboard::PutNumber("right flywheel speed", RobotMap::shooterRightFlywheel->GetSpeed());
	SmartDashboard::PutBoolean("gear limit switch" , Robot::gear->GetLimitSwitch());
	SmartDashboard::PutNumber("joystickz", Robot::oi->GetManualShooterSwivel());
	SmartDashboard::PutBoolean("joystick zbutton", Robot::oi->CDR_zPositiveAxis.Get());
	SmartDashboard::PutNumber("throttle adjustment", Robot::oi->GetTranslatedThrottle());
	SmartDashboard::PutBoolean("rev encoder", (RobotMap::shooterTurretSwivel->GetEncPosition() < -Robot::shooter->maxEncPosition));
	SmartDashboard::PutBoolean("fwd encoder", (RobotMap::shooterTurretSwivel->GetEncPosition() > Robot::shooter->maxEncPosition));
	SmartDashboard::PutBoolean("rev limit switch", RobotMap::shooterTurretSwivel->IsRevLimitSwitchClosed());
	SmartDashboard::PutBoolean("fwd limit switch", RobotMap::shooterTurretSwivel->IsFwdLimitSwitchClosed());
	//SmartDashboard::PutNumber("frame size", Robot::pixySubsystem->GetShooterPixyData().size());
	SmartDashboard::PutNumber("swivel speed", RobotMap::shooterTurretSwivel->Get());
	SmartDashboard::PutNumber("drivetrain left speed", RobotMap::drivetrainFrontLeftMotor->Get());
	SmartDashboard::PutNumber("drivetrain right speed", RobotMap::drivetrainFrontRightMotor->Get());

//	SmartDashboard::PutBoolean("leftA", RobotMap::leftA->Get());
//	SmartDashboard::PutBoolean("leftB", RobotMap::leftB->Get());
//	SmartDashboard::PutBoolean("RightA", RobotMap::RightA->Get());
//	SmartDashboard::PutBoolean("RightB", RobotMap::RightB->Get());
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);
