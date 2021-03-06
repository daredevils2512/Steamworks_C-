#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include "../RobotMap.h"
#include "CANTalon.h"
#include "../Nullable.h"
#include "../Subsystems/PixySubsystem.h"


class Shooter : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> flywheel;
	std::shared_ptr<CANTalon> turretSwivel;
	std::shared_ptr<CANTalon> spinCycleFeed;
	std::shared_ptr<CANTalon> bottomBooster;
	std::shared_ptr<CANTalon> topBooster;
	std::shared_ptr<frc::DoubleSolenoid> hoodActuator;

	//bools for comparisons later on
	bool lastConditionRight;
	bool lastConditionLeft;
	double shooterSpeed;
public:
	//creating all the usable functions
	double lastSetFlywheel = 0;
	Shooter();
	void InitDefaultCommand();
	void SaveFlywheelSpeed(double speed);
	void SetFlywheelSpeed(double speed);
	void RunFlywheel();
	void StopFlywheel();
	void SetBoosterSpeed(double speed);
	void SetSpinCycleFeedSpeed(double speed);
	void SetSwivelSpeed(double speed);
	double GetSwivelPosition();
	void ActuateHood(frc::DoubleSolenoid::Value direction);
	bool IsHoodActuated();
	double GetVirtualDistance(PixySubsystem::ObjectValues object);
	//int GetVirtualDistance(Pixy::ObjectValues object);
	double GetShooterSpeed();
	//the maximum encoder clicks we allow for the shooter's swivel
	double maxEncPosition;
};

#endif  // Shooter_H
