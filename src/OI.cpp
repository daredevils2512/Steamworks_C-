#include "OI.h"
#include "SmartDashboard/SmartDashboard.h"
#include "WPILib.h"
#include "Commands/Drive.h"

OI::OI()
{

	// Process operator interface input here.

}

double OI::GetX() {
	return driverController.GetRawAxis(1);

}
double OI::GetY() {
	return driverController.GetRawAxis(4);
}
