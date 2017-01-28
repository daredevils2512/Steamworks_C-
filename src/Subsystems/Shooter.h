#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include "../RobotMap.h"
#include "CANTalon.h"

class Shooter : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> LeftFlywheel;
	std::shared_ptr<CANTalon> RightFlywheel;
	std::shared_ptr<CANTalon> TurretSwivel;
	std::shared_ptr<CANTalon> SpinCycleFeed;

	std::shared_ptr<frc::DoubleSolenoid> LeftLimitSwitch;
	std::shared_ptr<frc::DoubleSolenoid> RightLimitSwitch;
	std::shared_ptr<frc::DoubleSolenoid> HoodActuator;

public:
	Shooter();
	void InitDefaultCommand();
	void SetFlywheelSpeed(double speed);
	void SetSpinCycleFeedSpeed(double speed);
	void SetSwivelSpeed(double speed);
	void ActuateHood(frc::DoubleSolenoid::Value direction);
	bool IsHoodActuated();
	bool IsLeftLimitSwitchPressed();
	bool IsRightLimitSwitchPressed();
};

#endif  // Shooter_H
