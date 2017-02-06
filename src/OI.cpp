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
	DRC_rightTrigger.WhenPressed(new DrivetrainShift(true));
	DRC_rightTrigger.WhenReleased(new DrivetrainShift(false));
	DRC_rightBumper.WhenPressed(new FloorIntakeRunMotor(0.8));
	DRC_leftBumper.WhenPressed(new FloorIntakeRunMotor(0.0));
	DRC_xButton.WhileHeld(new ClimberRunMotor(0.8));
	DRC_xButton.WhenReleased(new ClimberRunMotor(0.0));
	DRC_yButton.WhileHeld(new ClimberRunMotor(-0.8));
	DRC_yButton.WhenReleased(new ClimberRunMotor(0.0));

}

double OI::GetX() {
	//gets forward/backward values
	if(InvertDriving()) {
		return Desensitize(driverController.GetRawAxis(1));
	}else{
		return Desensitize(-driverController.GetRawAxis(1));
	}

}
double OI::GetY() {
	//gets turning values
	return driverController.GetRawAxis(4);
}

double OI::Desensitize(double value) {
	//set threshold so tiny values on the joystick don't register,
	//sometimes resting value of joystick is not 0
	if (fabs(value) < 0.2) value = 0;
	return value;
}

double OI::GetThrottle() {
	//get value of throttle axis
	return coDriverController.GetRawAxis(3);
}

bool OI::InvertDriving() {
	//for traversing defenses easier, invert forward/backward direction if
	//driver left trigger is held
	//also set controller to rumble, to inform driver controls are now inverted
	if(DRC_leftTrigger.Get()) {
		driverController.SetRumble(Joystick::kRightRumble, 1.0);
		return true;
	}else{
		driverController.SetRumble(Joystick::kRightRumble, 0.0);
		return false;
	}
}
bool OI::POVForward() {
	//detects if the POV hat is pushed forward or not
	if((coDriverController.GetPOV() >= 270) || (coDriverController.GetPOV() <= 90)) {
		return true;
	}else{
		return false;
	}
}

int OI::GetJoystickPOV() {
	//accesses the POV hat value
	return coDriverController.GetPOV();
}

