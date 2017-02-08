#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "WPILib.h"

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
std::shared_ptr<Pixy> RobotMap::shooterPixy;
std::shared_ptr<frc::RobotDrive> RobotMap::drivetrainChassis;
std::shared_ptr<frc::Relay> RobotMap::compressorSpike;
std::shared_ptr<frc::DigitalInput> RobotMap::compressorPressureSwitch;
std::shared_ptr<frc::DigitalInput> RobotMap::shooterLeftLimitSwitch;
std::shared_ptr<frc::DigitalInput> RobotMap::shooterRightLimitSwitch;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::drivetrainShift;
std::shared_ptr<frc::DigitalInput> RobotMap::gearLimitSwitch;
std::shared_ptr<frc::DigitalInput> RobotMap::gearPhotoeye;
std::shared_ptr<frc::SPI> RobotMap::gearRealPixy;
std::shared_ptr<frc::SPI> RobotMap::gearFakePixy;
std::shared_ptr<Pixy> RobotMap::gearPixy;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::gearSolenoid;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::shooterHoodActuator;

//runs at startup of robot
void RobotMap::init() {
	//assigns ports and settings to pointer objects declared in RobotMap.h
	//Creating new instances of the subsystems
	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();

	drivetrainFrontLeftMotor.reset (new CANTalon(1));
	lw->AddActuator("Drivetrain" , "FrontLeftMotor" , drivetrainFrontLeftMotor);
	//Setting the control mode of the front motors to slaves
	drivetrainFrontLeftMotor->SetControlMode(frc::CANSpeedController::kFollower);
	drivetrainFrontLeftMotor->Set(4);

	drivetrainRearLeftMotor.reset (new CANTalon(4));
	lw->AddActuator("Drivetrain" , "RearLeftMotor" , drivetrainRearLeftMotor);
	drivetrainRearLeftMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	drivetrainRearLeftMotor->ConfigEncoderCodesPerRev(128);
	//Setting up PID with the back motors since they are the Masters
	drivetrainRearLeftMotor->SetPID(0.0, 0.0, 0.0, 0.0);

	drivetrainFrontRightMotor.reset (new CANTalon(3));
	lw->AddActuator("Drivetrain" , "FrontRightMotor" , drivetrainFrontRightMotor);
	//Setting the control mode of the front motors to slaves
	drivetrainFrontRightMotor->SetControlMode(frc::CANSpeedController::kFollower);
	drivetrainFrontRightMotor->Set(2);

	drivetrainRearRightMotor.reset (new CANTalon(2));
	lw->AddActuator("Drivetrain" , "RearRightMotor" , drivetrainRearRightMotor);
	drivetrainRearRightMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	drivetrainRearRightMotor->ConfigEncoderCodesPerRev(128);
	//Setting up PID with the back motors since they are the Masters
	drivetrainRearRightMotor->SetPID(0.0, 0.0, 0.0, 0.0);

	climberMotor.reset (new CANTalon(5));
	lw->AddActuator("Climber" , "ClimberMotor" , climberMotor);

	intakeMotor.reset (new CANTalon(6));
	lw->AddActuator("FloorIntake" , "IntakeMotor" , intakeMotor);

	shooterLeftFlywheel.reset (new CANTalon(7));
	lw->AddActuator("Shooter" , "LeftFlywheel" , shooterLeftFlywheel);

	shooterRightFlywheel.reset (new CANTalon(8));
	lw->AddActuator("Shooter" , "RightFlywheel" , shooterRightFlywheel);

	shooterTurretSwivel.reset (new CANTalon(9));
	lw->AddActuator("Shooter" , "TurretSwivel" , shooterTurretSwivel);

	shooterSpinCycleFeed.reset (new CANTalon(10));
	lw->AddActuator("Shooter" , "SpinCycleFeed" , shooterSpinCycleFeed);

	shooterRealPixy.reset (new frc::SPI(frc::SPI::kOnboardCS0));
	shooterFakePixy.reset (new frc::SPI(frc::SPI::kOnboardCS2));

	shooterPixy.reset (new Pixy(shooterRealPixy, shooterFakePixy));

	//creating a new chassis consisting of all the drivetrain motors
	drivetrainChassis.reset (new frc::RobotDrive (drivetrainFrontLeftMotor , drivetrainRearLeftMotor , drivetrainFrontRightMotor , drivetrainRearRightMotor));

	drivetrainChassis ->SetSafetyEnabled(true);
		drivetrainChassis ->SetExpiration(0.5);
		drivetrainChassis ->SetSensitivity(0.5);
		drivetrainChassis ->SetMaxOutput(1.0);

	shooterHoodActuator.reset (new frc::DoubleSolenoid (1, 2, 3));
	lw ->AddActuator("Shooter", "HoodActuator", shooterHoodActuator);

	compressorSpike.reset(new frc::Relay(1));
	lw ->AddActuator("Compressor", "CompressorSpike", compressorSpike);

	compressorPressureSwitch.reset(new frc::DigitalInput(0));
	lw ->AddSensor("Compressor", "CompressorPressureSwitch", compressorPressureSwitch);

	drivetrainShift.reset (new frc::DoubleSolenoid (1, 0, 1));
	lw ->AddActuator("Drivetrain" , "DoubleSolenoid" , drivetrainShift);

	shooterLeftLimitSwitch.reset(new frc::DigitalInput(1));
	lw ->AddSensor("Shooter", "LeftLimitSwitch", shooterLeftLimitSwitch);

	shooterRightLimitSwitch.reset(new frc::DigitalInput(2));
	lw ->AddSensor ("Shooter" , "RightLimitSwitch" , shooterRightLimitSwitch);

	gearLimitSwitch.reset (new frc::DigitalInput(3));
	lw ->AddSensor("Gear" , "GearLimitSwitch" , gearLimitSwitch);

	gearRealPixy.reset (new frc::SPI(frc::SPI::kOnboardCS1));
	gearFakePixy.reset (new frc::SPI(frc::SPI::kOnboardCS3));

	gearPixy.reset (new Pixy(gearRealPixy, gearFakePixy));

	gearPhotoeye.reset (new frc::DigitalInput(4));
	lw ->AddSensor("Gear" , "GearPhotoeye" , gearPhotoeye);

	gearSolenoid.reset (new frc::DoubleSolenoid(2, 3, 4));
	lw ->AddActuator("Gear" , "GearSolenoid" , gearSolenoid);

}
