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
	previousGearSwitchState = gear->GetLimitSwitch();
  }

void Robot::DisabledInit(){
	compressor->SetClosedLoopControl(false);
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::UpdateGearActuator() {
	if(gear->GetLimitSwitch() != previousGearSwitchState){
		gear->SetCurrentCommand(new GearIntakeActuate(!gear->GetLimitSwitch()));
	}
	previousGearSwitchState = gear->GetLimitSwitch();
}

void Robot::AutonomousInit() {
	//starts autonomous
	std::string autoString = FileIO::getFileAsString("auto.txt");
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	UpdateGearActuator();
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
	UpdateGearActuator();
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
