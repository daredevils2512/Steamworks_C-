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
std::shared_ptr<frc::RobotDrive> RobotMap::drivetrainChassis;
std::shared_ptr<frc::Encoder> RobotMap::drivetrainLeftEncoder;
std::shared_ptr<frc::Encoder> RobotMap::drivetrainRightEncoder;
std::shared_ptr<frc::Relay> RobotMap::compressorSpike;
std::shared_ptr<frc::DigitalInput> RobotMap::compressorPressureSwitch;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::drivetrainShift;

//runs at startup of robot
void RobotMap::init() {
	//assigns ports and settings to pointer objects declared in RobotMap.h
	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();

	drivetrainFrontLeftMotor.reset (new CANTalon(1));
	lw -> AddActuator("Drivetrain" , "FrontLeftMotor" , drivetrainFrontLeftMotor);

	drivetrainRearLeftMotor.reset (new CANTalon(2));
	lw -> AddActuator("Drivetrain" , "RearLeftMotor" , drivetrainRearLeftMotor);

	drivetrainFrontRightMotor.reset (new CANTalon(3));
	lw -> AddActuator("Drivetrain" , "FrontRightMotor" , drivetrainFrontRightMotor);

	drivetrainRearRightMotor.reset (new CANTalon(4));
	lw -> AddActuator("Drivetrain" , "FrontRightMotor" , drivetrainRearRightMotor);

	climberMotor.reset (new CANTalon(5));

	intakeMotor.reset (new CANTalon(6));

	drivetrainChassis.reset (new frc::RobotDrive (drivetrainFrontLeftMotor , drivetrainRearLeftMotor , drivetrainFrontRightMotor , drivetrainRearRightMotor));

	drivetrainChassis ->SetSafetyEnabled(true);
		drivetrainChassis ->SetExpiration(0.5);
		drivetrainChassis ->SetSensitivity(0.5);
		drivetrainChassis ->SetMaxOutput(1.0);

	drivetrainLeftEncoder.reset (new frc::Encoder (0 , 1 , false , frc::Encoder::k4X));
	lw -> AddSensor("Drivetrain" , "LeftEncoder" , drivetrainLeftEncoder);
	drivetrainLeftEncoder ->SetDistancePerPulse(0.0981747704246);
	//took wheel diameter of 4 inches and multiplied by pi to get 12.56 inch circumference
	//then divided circumference by 128 clicks to get the distance per pulse value
	drivetrainRightEncoder.reset (new frc::Encoder (2 , 3 , false , frc::Encoder::k4X));
	lw -> AddSensor("Drivetrain" , "RightEncoder" , drivetrainRightEncoder);
	drivetrainRightEncoder ->SetDistancePerPulse(0.0981747704246);

	drivetrainShift.reset (new frc::DoubleSolenoid (1 , 0 , 1));
	lw -> AddActuator("Drivetrain" , "DoubleSolenoid" , drivetrainShift);

	compressorSpike.reset(new frc::Relay(1));
	lw -> AddActuator("Compressor", "CompressorSpike", compressorSpike);

	compressorPressureSwitch.reset(new frc::DigitalInput(1));
	lw -> AddSensor("Compressor", "CompressorPressureSwitch", compressorPressureSwitch);

}
