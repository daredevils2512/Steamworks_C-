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
std::shared_ptr<frc::Relay> RobotMap::compressorSpike;
std::shared_ptr<frc::DigitalInput> RobotMap::compressorPressureSwitch;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::drivetrainShift;
std::shared_ptr<frc::DigitalInput> RobotMap::gearLimitSwitch;
std::shared_ptr<frc::DigitalInput> RobotMap::gearPhotoeye;
std::shared_ptr<frc::SPI> RobotMap::gearRealPixy;
std::shared_ptr<frc::SPI> RobotMap::gearFakePixy;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::gearSolenoid;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::shooterHoodActuator;

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
	drivetrainRearLeftMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	drivetrainRearLeftMotor->ConfigEncoderCodesPerRev(256);
	//Setting up PID with the back motors since they are the Masters
	drivetrainRearLeftMotor->SetPID(0.0, 0.0, 0.0, 0.0);

	drivetrainFrontRightMotor.reset (new CANTalon(9));
	lw->AddActuator("Drivetrain" , "FrontRightMotor" , drivetrainFrontRightMotor);
	//Setting the control mode of the front motors to slaves

	drivetrainRearRightMotor.reset (new CANTalon(2));
	lw->AddActuator("Drivetrain" , "RearRightMotor" , drivetrainRearRightMotor);
	drivetrainRearRightMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	drivetrainRearRightMotor->ConfigEncoderCodesPerRev(256);
	//Setting up PID with the back motors since they are the Masters
	drivetrainRearRightMotor->SetPID(0.0, 0.0, 0.0, 0.0);

	climberMotor.reset (new CANTalon(8));
	lw->AddActuator("Climber" , "ClimberMotor" , climberMotor);

	intakeMotor.reset (new CANTalon(3));
	lw->AddActuator("FloorIntake" , "IntakeMotor" , intakeMotor);

	shooterLeftFlywheel.reset (new CANTalon(5));
	shooterLeftFlywheel->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	lw->AddActuator("Shooter" , "LeftFlywheel" , shooterLeftFlywheel);

	shooterRightFlywheel.reset (new CANTalon(7));
	shooterRightFlywheel->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	lw->AddActuator("Shooter" , "RightFlywheel" , shooterRightFlywheel);

	shooterTurretSwivel.reset (new CANTalon(6));
	lw->AddActuator("Shooter" , "TurretSwivel" , shooterTurretSwivel);
	shooterTurretSwivel->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	//shooterTurretSwivel->ConfigLimitMode(frc::CANSpeedController::kLimitMode_SwitchInputsOnly);

	shooterSpinCycleFeed.reset (new CANTalon(0));
	lw->AddActuator("Shooter" , "SpinCycleFeed" , shooterSpinCycleFeed);

	shooterRealPixy.reset (new frc::SPI(frc::SPI::kOnboardCS0));
	shooterFakePixy.reset (new frc::SPI(frc::SPI::kOnboardCS2));

	//creating a new chassis consisting of all the drivetrain motors
	drivetrainChassis.reset (new frc::RobotDrive (drivetrainFrontLeftMotor , drivetrainRearLeftMotor , drivetrainFrontRightMotor , drivetrainRearRightMotor));

	drivetrainChassis ->SetSafetyEnabled(true);
		drivetrainChassis ->SetExpiration(0.5);
		drivetrainChassis ->SetSensitivity(0.5);
		drivetrainChassis ->SetMaxOutput(1.0);

	shooterHoodActuator.reset (new frc::DoubleSolenoid (0, 1, 0));
	lw ->AddActuator("Shooter", "HoodActuator", shooterHoodActuator);

	compressorSpike.reset(new frc::Relay(1));
	lw ->AddActuator("Compressor", "CompressorSpike", compressorSpike);

	compressorPressureSwitch.reset(new frc::DigitalInput(0));
	lw ->AddSensor("Compressor", "CompressorPressureSwitch", compressorPressureSwitch);

	drivetrainShift.reset (new frc::DoubleSolenoid (0, 4, 5));
	lw ->AddActuator("Drivetrain" , "DoubleSolenoid" , drivetrainShift);

	gearLimitSwitch.reset (new frc::DigitalInput(3));
	lw ->AddSensor("Gear" , "GearLimitSwitch" , gearLimitSwitch);

	gearRealPixy.reset (new frc::SPI(frc::SPI::kOnboardCS1));
	gearFakePixy.reset (new frc::SPI(frc::SPI::kOnboardCS3));

	gearPhotoeye.reset (new frc::DigitalInput(4));
	lw ->AddSensor("Gear" , "GearPhotoeye" , gearPhotoeye);

	gearSolenoid.reset (new frc::DoubleSolenoid(0, 2, 3));
	lw ->AddActuator("Gear" , "GearSolenoid" , gearSolenoid);

}
