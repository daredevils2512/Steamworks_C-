#include "Robot.h"

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
//	frc::CameraServer::GetInstance()->StartAutomaticCapture();
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
	std::string autoString = FileIO::getFileAsString("auto.txt");
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	gear->UpdateGearActuator();
	Scheduler::GetInstance()->RemoveAll();
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	//stops autonomous command
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
	compressor->SetClosedLoopControl(true);
}

void Robot::TeleopPeriodic() {
	//gear->UpdateGearActuator();
	Scheduler::GetInstance()->Run();
	//prints information to the smart dashboard
	SmartDashboard::PutNumber("left encoder" , RobotMap::drivetrainFrontLeftMotor->GetEncPosition());
	SmartDashboard::PutNumber("right encoder", RobotMap::drivetrainFrontRightMotor->GetEncPosition());
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
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);
