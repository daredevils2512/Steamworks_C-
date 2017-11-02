#ifndef ROBOTMAP_H
#define ROBOTMAP_H
#include "WPILib.h"
#include "CANTalon.h"
#include "SPI.h"
#include <Encoder.h>

class RobotMap {
public:
	//speed controllers for drivetrain
	static std::shared_ptr<CANTalon> drivetrainFrontLeftMotor;
	static std::shared_ptr<CANTalon> drivetrainRearLeftMotor;
	static std::shared_ptr<CANTalon> drivetrainFrontRightMotor;
	static std::shared_ptr<CANTalon> drivetrainRearRightMotor;
	//speed controller for running the climber motor
	static std::shared_ptr<CANTalon> climberMotor;
	//speed controller for running the intake motor
	static std::shared_ptr<CANTalon> intakeMotor;
	//speed controllers for the shooter
	static std::shared_ptr<CANTalon> shooterFlywheel;
	static std::shared_ptr<CANTalon> shooterTurretSwivel;
	static std::shared_ptr<CANTalon> shooterSpinCycleFeed;
	static std::shared_ptr<CANTalon> shooterBottomBooster;
	static std::shared_ptr<CANTalon> shooterTopBooster;
	//pixy objects for the shooter
	//A fake pixy is needed because you need to toggle the pixy to receive data
	//because the roborio can't toggle the same pixy repeatedly
	static std::shared_ptr<frc::SPI> shooterRealPixy;
	static std::shared_ptr<frc::SPI> shooterFakePixy;
	//robot drivetrain
	static std::shared_ptr<frc::RobotDrive> drivetrainChassis;
	static std::shared_ptr<frc::Encoder> drivetrainLeftEncoder;
	static std::shared_ptr<frc::Encoder> drivetrainRightEncoder;
	//compressor switch and sensor to regulate compressor when connected to robot
	static std::shared_ptr<frc::Relay> compressorSpike;
	static std::shared_ptr<frc::DigitalInput> compressorPressureSwitch;
	//pneumatic actuator for shifting gears on drivetrain
	static std::shared_ptr<frc::DoubleSolenoid> drivetrainShift;
	//limit switch to notify once gear is in the slot
	static std::shared_ptr<frc::DigitalInput> gearLimitSwitch;
	//solenoid to actuate gear slot in and out
	static std::shared_ptr<frc::DoubleSolenoid> gearSolenoid;
	//solenoid to actuate the shooter hood forward and back
	static std::shared_ptr<frc::DoubleSolenoid> shooterHoodActuator;

    static std::shared_ptr<frc::Relay> spotlightRelay;


	static void init();
};
/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int LEFTMOTOR = 1;
// constexpr int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int RANGE_FINDER_PORT = 1;
// constexpr int RANGE_FINDER_MODULE = 1;
#endif  // ROBOTMAP_H
