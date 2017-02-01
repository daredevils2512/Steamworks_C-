#include "OI.h"
#include "SmartDashboard/SmartDashboard.h"
#include "WPILib.h"
#include "Commands/ClimberRunMotor.h"
#include "Commands/Drive.h"
#include "Commands/DrivetrainShift.h"
#include "Commands/FloorIntakeRunMotor.h"
#include "Commands/GearIntakeActuate.h"
#include "Commands/ShooterMoveHood.h"
#include "Commands/ShooterRunFlywheel.h"
#include "Commands/ShooterRunSpinCycleFeed.h"
#include "Commands/ShooterSwivelTurret.h"


OI::OI()
{
	// activates commands here based off of operator input
	DRC_rightTrigger.WhenReleased(new DrivetrainShift(false));
	DRC_rightTrigger.WhileHeld(new DrivetrainShift(true));

}

double OI::GetX() {
	//gets forward/backward values
	return driverController.GetRawAxis(1);

}
double OI::GetY() {
	//gets turning values
	return driverController.GetRawAxis(4);
}
