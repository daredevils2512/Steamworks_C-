#ifndef OI_H
#define OI_H

#include "WPILib.h"

//creates all of the inputs on the controllers
class OI
{
private:
	//declares controllers
	Joystick driverController{0};

	//driver controls
	JoystickButton DRC_rightBumper{&driverController, 6};
public:
	OI();
	//control related functions
	double GetX();
	double GetY();
};

#endif  // OI_H
