#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "WPILib.h"
#include "CANTAlon.h"

static const int DRIVETRAIN_FRONT_LEFT_MOTOR = 4;
static const int DRIVETRAIN_REAR_LEFT_MOTOR = 1;
static const int DRIVETRAIN_FRONT_RIGHT_MOTOR = 9;
static const int DRIVETRAIN_REAR_RIGHT_MOTOR = 2;
static const int CLIMBER_MOTOR = 8;
static const int INTAKE_MOTOR = 3;
static const int SHOOTER_FLYWHEEL = 5;
static const int SHOOTER_TURRET_SWIVEL = 6;
static const int SHOOTER_SPIN_CYCLE_FEED = 0;
static const int SHOOTER_BOTTOM_BOOSTER = 7;
static const int SHOOTER_TOP_BOOSTER =10;


//access pointer objects declared in RobotMap.h
std::shared_ptr<CANTalon> RobotMap::drivetrainFrontLeftMotor;
std::shared_ptr<CANTalon> RobotMap::drivetrainRearLeftMotor;
std::shared_ptr<CANTalon> RobotMap::drivetrainFrontRightMotor;
std::shared_ptr<CANTalon> RobotMap::drivetrainRearRightMotor;
std::shared_ptr<CANTalon> RobotMap::climberMotor;
std::shared_ptr<CANTalon> RobotMap::intakeMotor;
std::shared_ptr<CANTalon> RobotMap::shooterFlywheel;
std::shared_ptr<CANTalon> RobotMap::shooterTurretSwivel;
std::shared_ptr<CANTalon> RobotMap::shooterSpinCycleFeed;
std::shared_ptr<CANTalon> RobotMap::shooterBottomBooster;
std::shared_ptr<CANTalon> RobotMap::shooterTopBooster;
std::shared_ptr<frc::SPI> RobotMap::shooterRealPixy;
std::shared_ptr<frc::SPI> RobotMap::shooterFakePixy;
std::shared_ptr<frc::RobotDrive> RobotMap::drivetrainChassis;
std::shared_ptr<frc::Encoder> RobotMap::drivetrainLeftEncoder;
std::shared_ptr<frc::Encoder> RobotMap::drivetrainRightEncoder;
std::shared_ptr<frc::Relay> RobotMap::compressorSpike;
std::shared_ptr<frc::DigitalInput> RobotMap::compressorPressureSwitch;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::drivetrainShift;
std::shared_ptr<frc::DigitalInput> RobotMap::gearLimitSwitch;
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

	drivetrainFrontLeftMotor.reset (new CANTalon(DRIVETRAIN_FRONT_LEFT_MOTOR));
	lw->AddActuator("Drivetrain" , "FrontLeftMotor" , drivetrainFrontLeftMotor);
	drivetrainFrontLeftMotor->SetCurrentLimit(35);
	//Setting the control mode of the front motors to slaves

	drivetrainRearLeftMotor.reset (new CANTalon(DRIVETRAIN_REAR_LEFT_MOTOR));
	lw->AddActuator("Drivetrain" , "RearLeftMotor" , drivetrainRearLeftMotor);
	drivetrainRearLeftMotor->SetCurrentLimit(35);
	//Setting up PID with the back motors since they are the Masters

	drivetrainFrontRightMotor.reset (new CANTalon(DRIVETRAIN_FRONT_RIGHT_MOTOR));
	lw->AddActuator("Drivetrain" , "FrontRightMotor" , drivetrainFrontRightMotor);
	drivetrainFrontRightMotor->SetCurrentLimit(35);
	//Setting the control mode of the front motors to slaves

	drivetrainRearRightMotor.reset (new CANTalon(DRIVETRAIN_REAR_RIGHT_MOTOR));
	lw->AddActuator("Drivetrain" , "RearRightMotor" , drivetrainRearRightMotor);
	drivetrainRearRightMotor->SetCurrentLimit(35);
	//Setting up PID with the back motors since they are the Masters

	climberMotor.reset (new CANTalon(CLIMBER_MOTOR));
	lw->AddActuator("Climber" , "ClimberMotor" , climberMotor);
	climberMotor->SetCurrentLimit(37);

	intakeMotor.reset (new CANTalon(INTAKE_MOTOR));
	lw->AddActuator("FloorIntake" , "IntakeMotor" , intakeMotor);

	shooterFlywheel.reset (new CANTalon(SHOOTER_FLYWHEEL));
	shooterFlywheel->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	//shooterFlywheel->SetPID(0.062 , 0.000055, 4.0, 0.032);
	shooterFlywheel->SetPID(0.18,0.0000000011,0.0512,0.033);
	lw->AddActuator("Shooter" , "Flywheel" , shooterFlywheel);

	shooterTurretSwivel.reset (new CANTalon(SHOOTER_TURRET_SWIVEL));
	lw->AddActuator("Shooter" , "TurretSwivel" , shooterTurretSwivel);
	shooterTurretSwivel->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	//shooterTurretSwivel->ConfigLimitMode(frc::CANSpeedController::kLimitMode_SwitchInputsOnly);

	shooterSpinCycleFeed.reset (new CANTalon(SHOOTER_SPIN_CYCLE_FEED));
	lw->AddActuator("Shooter" , "SpinCycleFeed" , shooterSpinCycleFeed);

	shooterBottomBooster.reset(new CANTalon(SHOOTER_BOTTOM_BOOSTER));

	shooterTopBooster.reset(new CANTalon(SHOOTER_TOP_BOOSTER));

	shooterRealPixy.reset (new frc::SPI(frc::SPI::kOnboardCS0));
	shooterFakePixy.reset (new frc::SPI(frc::SPI::kOnboardCS2));

	//creating a new chassis consisting of all the drivetrain motors
	drivetrainChassis.reset (new frc::RobotDrive (drivetrainFrontLeftMotor , drivetrainRearLeftMotor , drivetrainFrontRightMotor , drivetrainRearRightMotor));

	drivetrainChassis ->SetSafetyEnabled(false);
		drivetrainChassis ->SetExpiration(0.5);
		drivetrainChassis ->SetSensitivity(0.5);
		drivetrainChassis ->SetMaxOutput(1.0);

	drivetrainLeftEncoder.reset(new frc::Encoder(1, 2, false, Encoder::k4X));//1, 2
	drivetrainLeftEncoder->SetReverseDirection(true);
	drivetrainLeftEncoder->SetDistancePerPulse(0.0349059176);

	drivetrainRightEncoder.reset(new frc::Encoder(3, 4, false, Encoder::k4X));//3, 4
	drivetrainRightEncoder->SetDistancePerPulse(0.0349059176);

	shooterHoodActuator.reset (new frc::DoubleSolenoid (0, 1, 0));
	lw ->AddActuator("Shooter", "HoodActuator", shooterHoodActuator);

	drivetrainShift.reset (new frc::DoubleSolenoid (0, 4, 5));
	lw ->AddActuator("Drivetrain" , "DoubleSolenoid" , drivetrainShift);

	gearSolenoid.reset (new frc::DoubleSolenoid (0 , 2, 3));

	gearLimitSwitch.reset (new frc::DigitalInput(0));
	lw ->AddSensor("Gear" , "GearLimitSwitch" , gearLimitSwitch);



//	gearRealPixy.reset (new frc::SPI(frc::SPI::kOnboardCS1));
//	gearFakePixy.reset (new frc::SPI(frc::SPI::kOnboardCS3));


}
