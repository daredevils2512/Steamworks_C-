#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "WPILib.h"
#include "CANTAlon.h"

//access pointer objects declared in RobotMap.h
std::shared_ptr<CANTalon> RobotMap::drivetrainFrontLeftMotor;
std::shared_ptr<CANTalon> RobotMap::drivetrainRearLeftMotor;
std::shared_ptr<CANTalon> RobotMap::drivetrainFrontRightMotor;
std::shared_ptr<CANTalon> RobotMap::drivetrainRearRightMotor;
std::shared_ptr<CANTalon> RobotMap::climberMotor;
std::shared_ptr<CANTalon> RobotMap::intakeMotor;
std::shared_ptr<CANTalon> RobotMap::shooterLeftFlywheel;
std::shared_ptr<CANTalon> RobotMap::shooterRightFlywheel;
std::shared_ptr<CANTalon> RobotMap::shooterTurretSwivel;
std::shared_ptr<CANTalon> RobotMap::shooterSpinCycleFeed;
std::shared_ptr<frc::SPI> RobotMap::shooterRealPixy;
std::shared_ptr<frc::SPI> RobotMap::shooterFakePixy;
std::shared_ptr<frc::RobotDrive> RobotMap::drivetrainChassis;
std::shared_ptr<frc::Encoder> RobotMap::drivetrainLeftEncoder;
std::shared_ptr<frc::Encoder> RobotMap::drivetrainRightEncoder;
std::shared_ptr<frc::Relay> RobotMap::compressorSpike;
std::shared_ptr<frc::DigitalInput> RobotMap::compressorPressureSwitch;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::drivetrainShift;
std::shared_ptr<frc::DigitalInput> RobotMap::gearLimitSwitch;
std::shared_ptr<frc::SPI> RobotMap::gearRealPixy;
std::shared_ptr<frc::SPI> RobotMap::gearFakePixy;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::gearSolenoid;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::shooterHoodActuator;
//std::shared_ptr<frc::DigitalInput> RobotMap::leftA;
//std::shared_ptr<frc::DigitalInput> RobotMap::leftB;
//std::shared_ptr<frc::DigitalInput> RobotMap::RightA;
//std::shared_ptr<frc::DigitalInput> RobotMap::RightB;

//runs at startup of robot
void RobotMap::init() {
	//assigns ports and settings to pointer objects declared in RobotMap.h
	//Creating new instances of the subsystems
	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();

	drivetrainFrontLeftMotor.reset (new CANTalon(4));
	lw->AddActuator("Drivetrain" , "FrontLeftMotor" , drivetrainFrontLeftMotor);
	//Setting the control mode of the front motors to slaves

	drivetrainRearLeftMotor.reset (new CANTalon(1));
	lw->AddActuator("Drivetrain" , "RearLeftMotor" , drivetrainRearLeftMotor);
	//Setting up PID with the back motors since they are the Masters

	drivetrainFrontRightMotor.reset (new CANTalon(9));
	lw->AddActuator("Drivetrain" , "FrontRightMotor" , drivetrainFrontRightMotor);
	//Setting the control mode of the front motors to slaves

	drivetrainRearRightMotor.reset (new CANTalon(2));
	lw->AddActuator("Drivetrain" , "RearRightMotor" , drivetrainRearRightMotor);
	//Setting up PID with the back motors since they are the Masters

	climberMotor.reset (new CANTalon(8));
	lw->AddActuator("Climber" , "ClimberMotor" , climberMotor);

	intakeMotor.reset (new CANTalon(3));
	lw->AddActuator("FloorIntake" , "IntakeMotor" , intakeMotor);

	shooterLeftFlywheel.reset (new CANTalon(5));
	shooterLeftFlywheel->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	shooterLeftFlywheel->SetPID(0.08 , 0.000065, 2, 0.0285);
	lw->AddActuator("Shooter" , "LeftFlywheel" , shooterLeftFlywheel);

	shooterRightFlywheel.reset (new CANTalon(7));
	shooterRightFlywheel->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	shooterRightFlywheel->SetPID(0.08, 0.000065, 2, 0.0285);
	lw->AddActuator("Shooter" , "RightFlywheel" , shooterRightFlywheel);

	shooterTurretSwivel.reset (new CANTalon(6));
	lw->AddActuator("Shooter" , "TurretSwivel" , shooterTurretSwivel);
	shooterTurretSwivel->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	//shooterTurretSwivel->ConfigLimitMode(frc::CANSpeedController::kLimitMode_SwitchInputsOnly);

	shooterSpinCycleFeed.reset (new CANTalon(0));
	lw->AddActuator("Shooter" , "SpinCycleFeed" , shooterSpinCycleFeed);

	shooterRealPixy.reset (new frc::SPI(frc::SPI::kOnboardCS0));
	shooterFakePixy.reset (new frc::SPI(frc::SPI::kOnboardCS1));

	//creating a new chassis consisting of all the drivetrain motors
	drivetrainChassis.reset (new frc::RobotDrive (drivetrainFrontLeftMotor , drivetrainRearLeftMotor , drivetrainFrontRightMotor , drivetrainRearRightMotor));

	drivetrainChassis ->SetSafetyEnabled(false);
		drivetrainChassis ->SetExpiration(0.5);
		drivetrainChassis ->SetSensitivity(0.5);
		drivetrainChassis ->SetMaxOutput(1.0);

	drivetrainLeftEncoder.reset(new frc::Encoder(1, 2, false, Encoder::k4X));//1, 2
	drivetrainLeftEncoder->SetReverseDirection(true);
	drivetrainLeftEncoder->SetDistancePerPulse(0.0349059176);
	//drivetrainLeftEncoder->SetDistancePerPulse(128);
	//drivetrainLeftEncoder->SetMaxPeriod(1.0);
	//drivetrainLeftEncoder->SetDistancePerPulse(0.0490873852123);

	drivetrainRightEncoder.reset(new frc::Encoder(3, 4, false, Encoder::k4X));//3, 4
	drivetrainRightEncoder->SetDistancePerPulse(0.0349059176);
	//drivetrainRightEncoder->SetDistancePerPulse(128);
	//drivetrainRightEncoder->SetMaxPeriod(1.0);
	//drivetrainRightEncoder->SetDistancePerPulse(0.0490873852123);

	shooterHoodActuator.reset (new frc::DoubleSolenoid (0, 1, 0));
	lw ->AddActuator("Shooter", "HoodActuator", shooterHoodActuator);

	drivetrainShift.reset (new frc::DoubleSolenoid (0, 4, 5));
	lw ->AddActuator("Drivetrain" , "DoubleSolenoid" , drivetrainShift);

	gearLimitSwitch.reset (new frc::DigitalInput(0));
	lw ->AddSensor("Gear" , "GearLimitSwitch" , gearLimitSwitch);

	gearRealPixy.reset (new frc::SPI(frc::SPI::kOnboardCS1));
	gearFakePixy.reset (new frc::SPI(frc::SPI::kOnboardCS3));

	gearSolenoid.reset (new frc::DoubleSolenoid(0, 2, 3));
	lw ->AddActuator("Gear" , "GearSolenoid" , gearSolenoid);

//	leftA.reset(new frc::DigitalInput(1));
//	leftB.reset(new frc::DigitalInput(2));
//	RightA.reset(new frc::DigitalInput(3));
//	RightB.reset(new frc::DigitalInput(4));

}
