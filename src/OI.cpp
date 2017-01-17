#include "OI.h"
#include "SmartDashboard/SmartDashboard.h"
#include "WPILib.h"
#include "Commands/Drive.h"
#include "Commands/DrivetrainShift.h"

OI::OI()
{
	// Process operator interface input here.
	DRC_rightBumper.WhenReleased(new DrivetrainShift(false));
	DRC_rightBumper.WhileHeld(new DrivetrainShift(true));
}

double OI::GetX() {
	return driverController.GetRawAxis(1);

}
double OI::GetY() {
	return driverController.GetRawAxis(4);
}
