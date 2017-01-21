#ifndef FloorIntake_H
#define FloorIntake_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "CANTalon.h"
#include <RobotMap.h>

class FloorIntake : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> intakeMotor;

	//creates usable functions
public:
	FloorIntake();
	void InitDefaultCommand();
	void SetSpeed(double speed);
};

#endif  // FloorIntake_H
