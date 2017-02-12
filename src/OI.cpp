#include "OI.h"
#include "SmartDashboard/SmartDashboard.h"
#include "WPILib.h"
#include "Commands/_CMG_ShootBall.h"
#include "Commands/ClimberRunMotor.h"
#include "Commands/Drive.h"
#include "Commands/DrivetrainShift.h"
#include "Commands/FloorIntakeRunMotor.h"
#include "Commands/GearIntakeActuate.h"
#include "Commands/ShooterMoveHood.h"
#include "Commands/ShooterRunFlywheel.h"
#include "Commands/ShooterRunSpinCycleFeed.h"
#include "Commands/ShooterSwivelTurret.h"
#include "Commands/ShooterVisionTrack.h"
#include "Commands/ShooterManualSwivel.h"
#include "Commands/ShooterManualRunFlywheel.h"


OI::OI()
{
	// activates commands here based off of operator input
	DRC_rightTrigger.WhenPressed(new DrivetrainShift(true));//working
	DRC_rightTrigger.WhenReleased(new DrivetrainShift(false));//working
	DRC_rightBumper.WhenPressed(new FloorIntakeRunMotor(-0.9));//working
	DRC_leftBumper.WhenPressed(new FloorIntakeRunMotor(0.0));//working
	DRC_xButton.WhileHeld(new ClimberRunMotor(-0.8));//working
	DRC_xButton.WhenReleased(new ClimberRunMotor(0.0));//working
	DRC_yButton.WhileHeld(new ClimberRunMotor(0.8));//working
	DRC_yButton.WhenReleased(new ClimberRunMotor(0.0));//working

	CDR_trigger.WhileHeld(new _CMG_ShootBall());//working
	CDR_trigger.WhenReleased(new ShooterRunFlywheel(0.0));//working
	CDR_trigger.WhenReleased(new ShooterRunSpinCycleFeed(0.0));//working
	CDR_joystickPOV.WhenPressed(new ShooterMoveHood(POVHoodControl()));//actuates one direction (forward)
	CDR_sideJoystickButton.WhileHeld(new ShooterVisionTrack());
	CDR_topLeftJoystick.WhileHeld(new FloorIntakeRunMotor(-0.9));//working
	CDR_topLeftJoystick.WhenReleased(new FloorIntakeRunMotor(0.0));//working
	CDR_bottomLeftJoystick.WhenPressed(new GearIntakeActuate(frc::DoubleSolenoid::kForward));
	CDR_bottomLeftJoystick.WhenReleased(new GearIntakeActuate(frc::DoubleSolenoid::kReverse));
	CDR_topRightJoystick.WhileHeld(new ClimberRunMotor(0.8));
	CDR_topRightJoystick.WhenReleased(new ClimberRunMotor(0.0));
	CDR_bottomRightJoystick.WhileHeld(new ClimberRunMotor(-0.8));
	CDR_bottomRightJoystick.WhenReleased(new ClimberRunMotor(0.0));
	CDR_bottomRightBase.WhenPressed(new ShooterRunFlywheel(0.4));//working
	CDR_topRightBase.WhenPressed(new ShooterRunFlywheel(0.5));//working
	CDR_bottomLeftBase.WhenPressed(new ShooterRunSpinCycleFeed(0.8));//working
	CDR_topLeftBase.WhenPressed(new ShooterRunSpinCycleFeed(0.0));//working
	CDR_topMiddleBase.WhenPressed(new ShooterRunFlywheel(0.0));//working, sometimes wheels spurt randomly
	CDR_zPositiveAxis.WhileHeld(new ShooterManualSwivel());
	CDR_zPositiveAxis.WhenReleased(new ShooterSwivelTurret(0.0));
	CDR_zNegativeAxis.WhileHeld(new ShooterManualSwivel());
	CDR_zNegativeAxis.WhenReleased(new ShooterSwivelTurret(0.0));
	CDR_throttle.WhileHeld(new ShooterManualRunFlywheel());
	CDR_throttle.WhenReleased(new ShooterRunFlywheel(0.0));

	CDB_bigWhite.WhenPressed(new ShooterMoveHood(frc::DoubleSolenoid::kForward));//working
	CDB_bigRed.WhenPressed(new ShooterMoveHood(frc::DoubleSolenoid::kReverse));//working
	CDB_green.WhileHeld(new FloorIntakeRunMotor(0.8));
	CDB_green.WhenReleased(new FloorIntakeRunMotor(0.0));
	CDB_yellow.WhenPressed(new GearIntakeActuate(frc::DoubleSolenoid::kForward));
	CDB_yellow.WhenReleased(new GearIntakeActuate(frc::DoubleSolenoid::kReverse));
	CDB_bottomWhite.WhileHeld(new ClimberRunMotor(0.8));
	CDB_bottomWhite.WhenReleased(new ClimberRunMotor(0.0));
	CDB_bottomRed.WhileHeld(new ClimberRunMotor(-0.8));
	CDB_bottomRed.WhenReleased(new ClimberRunMotor(0.0));
	CDB_topWhite.WhenPressed(new ShooterRunFlywheel(0.6));
	CDB_topRed.WhenPressed(new ShooterRunFlywheel(0.8));
	CDB_middleWhite.WhileHeld(new ShooterSwivelTurret(1.0));//working
	CDB_middleWhite.WhenReleased(new ShooterSwivelTurret(0.0));//working
	CDB_middleRed.WhileHeld(new ShooterSwivelTurret(-1.0));//working
	CDB_middleRed.WhenReleased(new ShooterSwivelTurret(0.0));//working
}

double OI::GetTurn() {
	//gets forward/backward values
	if(InvertDriving()) {
		return Desensitize(driverController.GetRawAxis(4));
	}else{
		return Desensitize(-driverController.GetRawAxis(4));
	}

}
double OI::GetMove() {
	//gets turning values
	return Desensitize(-driverController.GetRawAxis(1));
}

double OI::Desensitize(double value) {
	//set threshold so tiny values on the joystick don't register,
	//sometimes resting value of joystick is not 0
	if (fabs(value) < 0.3) value = 0;
	return value;
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
frc::DoubleSolenoid::Value OI::POVHoodControl() {
	//detects if the POV hat is pushed forward or not
	if((coDriverController.GetPOV() >= 270) || (coDriverController.GetPOV() <= 90)) {
		return frc::DoubleSolenoid::kForward;
	}else{
		return frc::DoubleSolenoid::kReverse;
	}
}

int OI::GetJoystickPOV() {
	//accesses the POV hat value
	return coDriverController.GetPOV();
}

double OI::GetManualShooterSwivel() {
	return coDriverController.GetRawAxis(2);
}

double OI::GetTranslatedThrottle() {
		return (coDriverController.GetRawAxis(3) + 1) / 2;
}

