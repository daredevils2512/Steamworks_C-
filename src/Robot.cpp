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
//	frc::CameraServer::GetInstance()->StartAutomaticCapture();
//	frc::CameraServer::GetInstance()->StartAutomaticCapture();
	terminateAutoGear = false;
	std::cout<<"Setting up VisionServer"<<std::endl;
	VisionServer::setupServer();
	std::thread(VisionServer::visionLoop).detach();
  }
void Robot::RobotPeriodic() {
	SmartDashboard::PutBoolean("Gear Sees Target", (VisionServer::targets.size() > 0));
}
void Robot::DisabledInit(){
	compressor->SetClosedLoopControl(false);
	VisionServer::isActive = false;
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
	SmartDashboard::PutBoolean("gear limit switch" , Robot::gear->GetLimitSwitch());
}

void Robot::AutonomousInit() {
	//starts autonomous
	VisionServer::isActive = true;
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
		std::cout << firstPart << " - " << lastPart << std::endl;
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
	VisionServer::isActive = true;
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
	RobotMap::drivetrainFrontLeftMotor->EnableCurrentLimit(true);
	RobotMap::drivetrainRearLeftMotor->EnableCurrentLimit(true);
	RobotMap::drivetrainFrontRightMotor->EnableCurrentLimit(true);
	RobotMap::drivetrainRearRightMotor->EnableCurrentLimit(true);
	RobotMap::climberMotor->EnableCurrentLimit(true);
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	//prints information to the smart dashboard
	SmartDashboard::PutNumber("swivel encoder", RobotMap::shooterTurretSwivel->GetEncPosition());
	SmartDashboard::PutNumber("left flywheel speed", RobotMap::shooterFlywheel->GetSpeed());
	SmartDashboard::PutBoolean("gear limit switch" , Robot::gear->GetLimitSwitch());
	SmartDashboard::PutNumber("left encoder", RobotMap::drivetrainLeftEncoder->GetDistance());
//	SmartDashboard::PutBoolean("left encoder digitalcheck", RobotMap::drivetrainLeftEncoder->CheckDigitalChannel(2));
	SmartDashboard::PutNumber("right encoder", RobotMap::drivetrainRightEncoder->GetDistance());
//	SmartDashboard::PutBoolean("right encoder digitalcheck", RobotMap::drivetrainRightEncoder->CheckDigitalChannel(4));
	SmartDashboard::PutNumber("subsystem get left encoder", Robot::drivetrain->GetLeftEncoder());
	SmartDashboard::PutNumber("subsystem get right encoder", Robot::drivetrain->GetRightEncoder());
	SmartDashboard::PutNumber("left encoder raw", RobotMap::drivetrainLeftEncoder->Get());
	SmartDashboard::PutNumber("right encoder raw", RobotMap::drivetrainRightEncoder->Get());
	SmartDashboard::PutNumber("front left current", RobotMap::drivetrainFrontLeftMotor->GetOutputCurrent());
	SmartDashboard::PutNumber("front right current", RobotMap::drivetrainFrontRightMotor->GetOutputCurrent());
	SmartDashboard::PutNumber("back left current", RobotMap::drivetrainRearLeftMotor->GetOutputCurrent());
	SmartDashboard::PutNumber("back right current", RobotMap::drivetrainRearRightMotor->GetOutputCurrent());
	SmartDashboard::PutNumber("flywheel current", RobotMap::shooterFlywheel->GetOutputCurrent());
	SmartDashboard::PutNumber("top booster current", RobotMap::shooterTopBooster->GetOutputCurrent());
	SmartDashboard::PutNumber("bottom booster current", RobotMap::shooterBottomBooster->GetOutputCurrent());
	SmartDashboard::PutNumber("swivel current", RobotMap::shooterTurretSwivel->GetOutputCurrent());
	SmartDashboard::PutNumber("floor intake current", RobotMap::intakeMotor->GetOutputCurrent());
	SmartDashboard::PutNumber("climber current", RobotMap::climberMotor->GetOutputCurrent());
	SmartDashboard::PutNumber("spin cycle current", RobotMap::shooterSpinCycleFeed->GetOutputCurrent());
	SmartDashboard::PutBoolean("gear intake actuate", Robot::gear->GetIntake());


	std::string toput = ":O";

	if(shooter->lastSetFlywheel == oi->SHOOT_BOILER_RPM){
			toput = "Boiler (HOOD BACK)";

	}else if(shooter->lastSetFlywheel == oi->SHOOT_BOILER_PEG_RPM){
			toput = "Boiler Peg";

	}else if(shooter->lastSetFlywheel == oi->SHOOT_CENTER_PEG_RPM){
			toput = "Center Peg";

	}else if(shooter->lastSetFlywheel == oi->SHOOT_FAR_HOPPER_RPM){
			toput = "Far Hopper";

	}else if(shooter->lastSetFlywheel == oi->SHOOT_CLOSE_HOPPER_RPM){
		toput = "Close Hopper (HOOD BACK)";
	}else{
			toput = "Manual??";
	}

	SmartDashboard::PutNumber("PERSIST current fly speed",shooter->lastSetFlywheel);
	SmartDashboard::PutString("PERSIST current speed mode", toput);

//	if(Robot::oi->GetB_Button()) {
//		terminateAutoGear = true;
//	}
//
//	if((!Robot::oi->GetLeftBumper()) && (terminateAutoGear == false)) {
//		if(Robot::gear->GetReleaseLimitSwitch()){
//			Robot::gear->ActuateGearRelease(frc::DoubleSolenoid::kForward);
//		}else{
//			Robot::gear->ActuateGearRelease(frc::DoubleSolenoid::kReverse);
//		}
//	}
//	frc::SmartDashboard::PutNumber("Targets",VisionServer::targets.size());
//	frc::SmartDashboard::PutBoolean("setupSucceeded",VisionServer::hasSetup);
//	frc::SmartDashboard::PutBoolean("isActive",VisionServer::isActive);
//	frc::SmartDashboard::PutBoolean("isConnected",VisionServer::isConnected());
	if(VisionServer::targets.size() > 0){
		double targetX = -1;
		for(int i = 0; i < VisionServer::targets.size(); i++){
			double thisX = VisionServer::targets[0].x;
			if(thisX > targetX){
				targetX = thisX;
			}
		}
		frc::SmartDashboard::PutNumber("TargetX",targetX);
	}
}

void Robot::TestPeriodic() {
	//lw->Run();
}

START_ROBOT_CLASS(Robot);
