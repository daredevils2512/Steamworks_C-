#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "WPILib.h"

std::shared_ptr<CANTalon> RobotMap::drivetrainFrontLeftMotor;
std::shared_ptr<CANTalon> RobotMap::drivetrainRearLeftMotor;
std::shared_ptr<CANTalon> RobotMap::drivetrainFrontRightMotor;
std::shared_ptr<CANTalon> RobotMap::drivetrainRearRightMotor;
std::shared_ptr<RobotDrive> RobotMap::drivetrainChassis;
std::shared_ptr<Encoder> RobotMap::drivetrainLeftEncoder;
std::shared_ptr<Encoder> RobotMap::drivetrainRightEncoder;
std::shared_ptr<Relay> RobotMap::compressorSpike;
std::shared_ptr<DigitalInput> RobotMap::compressorPressureSwitch;
std::shared_ptr<DoubleSolenoid> RobotMap::drivetrainShift;


void RobotMap::init() {
	LiveWindow *lw = LiveWindow::GetInstance();

	drivetrainFrontLeftMotor.reset (new CANTalon(1));
	lw ->AddActuator("Drivetrain" , "FrontLeftMotor" , drivetrainFrontLeftMotor);

	drivetrainRearLeftMotor.reset (new CANTalon(2));
	lw ->AddActuator("Drivetrain" , "RearLeftMotor" , drivetrainRearLeftMotor);

	drivetrainFrontRightMotor.reset (new CANTalon(3));
	lw ->AddActuator("Drivetrain" , "FrontRightMotor" , drivetrainFrontRightMotor);

	drivetrainRearRightMotor.reset (new CANTalon(4));
	lw -> AddActuator("Drivetrain" , "FrontRightMotor" , drivetrainRearRightMotor);

	drivetrainChassis.reset (new RobotDrive (drivetrainFrontLeftMotor , drivetrainRearLeftMotor , drivetrainFrontRightMotor , drivetrainRearRightMotor));

	drivetrainChassis ->SetSafetyEnabled(true);
		drivetrainChassis ->SetExpiration(0.5);
		drivetrainChassis ->SetSensitivity(0.5);
		drivetrainChassis ->SetMaxOutput(1.0);

	drivetrainLeftEncoder.reset (new Encoder (0 , 1 , false));
	lw ->AddSensor("Drivetrain" , "LeftEncoder" , drivetrainLeftEncoder);

	drivetrainRightEncoder.reset (new Encoder (2 , 3 , false));
	lw ->AddSensor("Drivetrain" , "RightEncoder" , drivetrainRightEncoder);

	drivetrainShift.reset (new DoubleSolenoid (1 , 2 , 3));
	lw ->AddActuator("Drivetrain" , "DoubleSolenoid" , drivetrainShift);

	compressorSpike.reset(new Relay(1));
	lw->AddActuator("Compressor", "CompressorSpike", compressorSpike);

	compressorPressureSwitch.reset(new DigitalInput(1));
	lw->AddSensor("Compressor", "CompressorPressureSwitch", compressorPressureSwitch);

}
