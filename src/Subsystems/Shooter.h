#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include "../RobotMap.h"
#include "CANTalon.h"
#include "../Nullable.h"


class Shooter : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> leftFlywheel;
	std::shared_ptr<CANTalon> rightFlywheel;
	std::shared_ptr<CANTalon> turretSwivel;
	std::shared_ptr<CANTalon> spinCycleFeed;

	std::shared_ptr<frc::DoubleSolenoid> hoodActuator;

	bool lastConditionRight;
	bool lastConditionLeft;
public:
	Shooter();
	void InitDefaultCommand();
	void SetFlywheelSpeed(double speed);
	void SetSpinCycleFeedSpeed(double speed);
	void SetSwivelSpeed(double speed);
	void ActuateHood(frc::DoubleSolenoid::Value direction);
	void SwivelVisionBased(Nullable< std::vector<int> > object);
	bool IsHoodActuated();
	int GetVirtualDistance(Pixy::ObjectValues object);
	//int GetVirtualDistance(Pixy::ObjectValues object);
	double maxEncPosition;
};

#endif  // Shooter_H
