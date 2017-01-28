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

public:
	Shooter();
	void InitDefaultCommand();
};

#endif  // Shooter_H
