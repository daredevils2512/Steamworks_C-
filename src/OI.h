#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "XboxController.h"

//creates all of the inputs on the controllers
class OI
{
private:
	//declares controllers
	XboxController driverController{0};
	Joystick coDriverController{1};


	//driver controls
	JoystickButton DRC_rightTrigger{&driverController, 3};
	JoystickButton DRC_leftTrigger{&driverController, 2};

	JoystickButton CDR_trigger{&coDriverController, 1};
	JoystickButton CDR_sideJoystickButton{&coDriverController, 2};
	JoystickButton CDR_bottomLeftJoystick{&coDriverController, 3};
	JoystickButton CDR_topLeftJoystick{&coDriverController, 5};
	JoystickButton CDR_bottomRightJoystick{&coDriverController, 4};
	JoystickButton CDR_topRightJoystick{&coDriverController, 6};
	JoystickButton CDR_bottomLeftBase{&coDriverController, 7};
	JoystickButton CDR_topLeftBase{&coDriverController, 8};
	JoystickButton CDR_bottomMiddleBase{&coDriverController, 9};
	JoystickButton CDR_topMiddleBase{&coDriverController, 10};
	JoystickButton CDR_bottomRightBase{&coDriverController, 11};
	JoystickButton CDR_topRightBase{&coDriverController, 12};
public:
	OI();
	//control related functions
	double GetX();
	double GetY();
};

#endif  // OI_H
