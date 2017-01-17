#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI
{
private:
	Joystick driverController{0};
	JoystickButton DRC_rightBumper{&driverController, 6};
public:
	OI();
	double GetX();
	double GetY();
};

#endif  // OI_H
