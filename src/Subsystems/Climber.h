#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "CANTalon.h"
#include <RobotMap.h>

class Climber : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> motor;

public:
	Climber();
	void InitDefaultCommand();
	void SetSpeed(double speed);

};

#endif  // Climber_H
