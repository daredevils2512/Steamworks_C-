#include "Robot.h"

//access pointer objects delcared in Robot.h
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<CompressorSubsystem> Robot::compressor;
std::shared_ptr<Climber> Robot::climber;
std::unique_ptr<OI> Robot::oi;

void Robot::RobotInit() {
    drivetrain.reset(new Drivetrain());
    compressor.reset(new CompressorSubsystem());
    climber.reset(new Climber());
	oi.reset(new OI());

  }

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
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
	SmartDashboard::PutNumber("left encoder", RobotMap::drivetrainLeftEncoder->GetDistance());
	SmartDashboard::PutNumber("right encoder", RobotMap::drivetrainRightEncoder->GetDistance());
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);
