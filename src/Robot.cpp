#include "Robot.h"

//access pointer objects declared in Robot.h
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<CompressorSubsystem> Robot::compressor;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<FloorIntake> Robot::floorIntake;
std::shared_ptr<Gear> Robot::gear;
std::shared_ptr<Shooter> Robot::shooter;
std::unique_ptr<OI> Robot::oi;

void Robot::RobotInit() {
	//starts subsystems and creates new instances of them
    drivetrain.reset(new Drivetrain());
    compressor.reset(new CompressorSubsystem());
    climber.reset(new Climber());
    floorIntake.reset(new FloorIntake());
    gear.reset(new Gear());
    shooter.reset(new Shooter());
    //starts operator interface
	oi.reset(new OI());
  }

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	//starts autonomous
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();

	Robot::drivetrain->ResetEncoders();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	//stops autonomous command
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	//prints information to the smart dashboard
	SmartDashboard::PutNumber("left encoder" , RobotMap::drivetrainFrontLeftMotor->GetEncPosition());
	SmartDashboard::PutNumber("right encoder", RobotMap::drivetrainFrontRightMotor ->GetEncPosition());
	SmartDashboard::PutBoolean("limit switch" , RobotMap::gearLimitSwitch ->Get());
	SmartDashboard::PutBoolean("gear photoeye", RobotMap::gearPhotoeye ->Get());
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);
