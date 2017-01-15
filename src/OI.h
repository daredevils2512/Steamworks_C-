#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI
{
private:
	Joystick driverController{0};
public:
	OI();
	double GetX();
	double GetY();
};

#endif  // OI_H
