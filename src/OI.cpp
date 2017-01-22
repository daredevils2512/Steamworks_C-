#include "OI.h"
#include "SmartDashboard/SmartDashboard.h"
#include "WPILib.h"
#include "Commands/Drive.h"
#include "Commands/DrivetrainShift.h"

OI::OI()
{
	// activates commands here based off of operator input
	DRC_rightBumper.WhenReleased(new DrivetrainShift(false));
	DRC_rightBumper.WhileHeld(new DrivetrainShift(true));
}

double OI::GetX() {
	//gets forward/backward values
	return driverController.GetRawAxis(1);

}
double OI::GetY() {
	//gets turning values
	return driverController.GetRawAxis(4);
}
