#include <Commands/AutoCircleDrive.h>
#include "OI.h"
#include "SmartDashboard/SmartDashboard.h"
#include "WPILib.h"
#include "Commands/_CMG_ShootBall.h"
#include "Commands/_CMG_ShootBall_BoosterWatchdog.h"
#include "Commands/ClimberRunMotor.h"
#include "Commands/Drive.h"
#include "Commands/DrivetrainShift.h"
#include "Commands/FloorIntakeRunMotor.h"
#include "Commands/GearIntakeActuate.h"
#include "Commands/ShooterMoveHood.h"
#include "Commands/ShooterRunFlywheel.h"
#include "Commands/ShooterSetFlywheelSpeed.h"
#include "Commands/ShooterRunSpinCycleFeed.h"
#include "Commands/ShooterSwivelTurret.h"
#include "Commands/ShooterVisionTrack.h"
#include "Commands/ShooterManualSwivel.h"
#include "Commands/ShooterManualRunFlywheel.h"
#include "Commands/ShooterPOVHoodControl.h"
#include "Commands/ShooterStartFlywheel.h"
#include "Commands/ShooterStopFlywheel.h"
#include "Commands/_CMG_ShooterManualSwivel.h"
#include "Commands/GearToggleIntake.h"
#include "Commands/AutoStraightDrive.h"
#include "Commands/AutoDimeSpin.h"
#include "Commands/_CMG_AutonomousGearFarPeg.h"
#include "Commands/GearVisionTurn.h"
#include "Commands/ShooterSwivelMoveToPosition.h"
#include "Commands/ShooterRunBoosters.h"
#include "Commands/ConditionallyReleaseGear.h"
#include "Commands/GearReleaseActuate.h"


OI::OI()
{
	// activates commands here based off of operator input
	DRC_rightTrigger.WhenPressed(new DrivetrainShift(true));//working
	DRC_rightTrigger.WhenReleased(new DrivetrainShift(false));//working
//	DRC_rightBumper.WhenPressed(new FloorIntakeRunMotor(-1.0));//working
//	DRC_leftBumper.WhenPressed(new FloorIntakeRunMotor(0.0));//working
	DRC_rightBumper.WhenPressed(new GearReleaseActuate(frc::DoubleSolenoid::kForward));
	DRC_leftBumper.WhenPressed(new GearReleaseActuate(frc::DoubleSolenoid::kReverse));
	DRC_xButton.WhileHeld(new ClimberRunMotor(1.0));//working
	DRC_xButton.WhenReleased(new ClimberRunMotor(0.0));//working
	DRC_yButton.WhileHeld(new FloorIntakeRunMotor(1.0));//working
	DRC_yButton.WhenReleased(new FloorIntakeRunMotor(0.0));//working
	DRC_leftjoystickButton.WhileHeld(new ConditionallyReleaseGear());
//	DRC_aButton.WhenPressed(new GearIntakeActuate(frc::DoubleSolenoid::kForward));//working
//	DRC_bButton.WhenPressed(new GearIntakeActuate(frc::DoubleSolenoid::kReverse));//working
	DRC_startButton.WhenPressed(new ClimberRunMotor(1.0));

	CDR_trigger.WhileHeld(new _CMG_ShootBall());//working
	//CDR_trigger.WhenReleased(new ShooterRunFlywheel(0.0));//working
	CDR_trigger.WhenReleased(new ShooterRunSpinCycleFeed(0.0));//working
	CDR_trigger.WhenReleased(new ShooterRunBoosters(0.0));
	CDR_trigger.WhenReleased(new ShooterStopFlywheel());
	CDR_joystickPOV.WhenPressed(new ShooterPOVHoodControl());//working
	CDR_sideJoystickButton.WhileHeld(new ShooterVisionTrack(false));//working
	CDR_topLeftJoystick.WhileHeld(new FloorIntakeRunMotor(-1.0));//working
	CDR_topLeftJoystick.WhenReleased(new FloorIntakeRunMotor(0.0));//working
	CDR_bottomLeftJoystick.WhenPressed(new GearToggleIntake());//working
	CDR_topRightJoystick.WhileHeld(new ClimberRunMotor(1.0));//working
	CDR_topRightJoystick.WhenReleased(new ClimberRunMotor(0.0));//working
	CDR_bottomRightJoystick.WhileHeld(new ClimberRunMotor(-1.0));//working
	CDR_bottomRightJoystick.WhenReleased(new ClimberRunMotor(0.0));//working
	CDR_bottomRightBase.WhenPressed(new ShooterRunBoosters(0.0));
	CDR_topRightBase.WhenPressed(new ShooterRunBoosters(0.8));
	CDR_bottomLeftBase.WhenPressed(new ShooterRunSpinCycleFeed(0.95));//working
	CDR_topLeftBase.WhenPressed(new ShooterRunSpinCycleFeed(0.0));//working
	CDR_topMiddleBase.WhenPressed(new ShooterRunFlywheel(0.0));//working, sometimes wheels spurt randomly
	CDR_bottomMiddleBase.WhileHeld(new ShooterRunSpinCycleFeed(-0.95));
	CDR_bottomMiddleBase.WhenReleased(new ShooterRunSpinCycleFeed(0.0));
	CDR_zPositiveAxis.WhileHeld(new ShooterManualSwivel());//working
	CDR_zPositiveAxis.WhenReleased(new ShooterSwivelTurret(0.0));//working
	CDR_zNegativeAxis.WhileHeld(new ShooterManualSwivel());//working
	CDR_zNegativeAxis.WhenReleased(new ShooterSwivelTurret(0.0));//working
	CDR_throttle.WhileHeld(new ShooterManualRunFlywheel());//working
	CDR_throttle.WhenReleased(new ShooterRunFlywheel(0.0));//working

	CDB_bigWhite.WhenPressed(new ShooterMoveHood(frc::DoubleSolenoid::kForward));//working
	CDB_bigRed.WhenPressed(new ShooterMoveHood(frc::DoubleSolenoid::kReverse));//working
	/*CDB_green.WhileHeld(new FloorIntakeRunMotor(1.0));//working
	CDB_green.WhenReleased(new FloorIntakeRunMotor(0.0));//working*/
	CDB_yellow.WhileHeld(new _CMG_ShootBall_BoosterWatchdog()/*new ShooterSwivelMoveToPosition(-8000)*/);//-7565
	CDB_yellow.WhenReleased(new ShooterRunSpinCycleFeed(0.0));//working
	CDB_yellow.WhenReleased(new ShooterRunBoosters(0.0));
	CDB_yellow.WhenReleased(new ShooterStopFlywheel());
//	CDB_yellow.WhenPressed(new GearVisionTurn(210));
	/*CDB_bottomWhite.WhileHeld(new ClimberRunMotor(1.0));//working
	CDB_bottomWhite.WhenReleased(new ClimberRunMotor(0.0));//working
	CDB_bottomRed.WhileHeld(new ClimberRunMotor(-0.8));//working
	CDB_bottomRed.WhenReleased(new ClimberRunMotor(0.0));//working*/

	CDB_topWhite.WhenPressed(new ShooterSetFlywheelSpeed(SHOOT_BOILER_RPM));
	CDB_topRed.WhenPressed(new ShooterSetFlywheelSpeed(SHOOT_FAR_HOPPER_RPM));
	CDB_middleWhite.WhenPressed(new ShooterSetFlywheelSpeed(SHOOT_BOILER_PEG_RPM)/*new _CMG_ShooterManualSwivel(0.2)*/);
	CDB_middleRed.WhenPressed(new ShooterSetFlywheelSpeed(SHOOT_CENTER_PEG_RPM)/*new _CMG_ShooterManualSwivel(-0.2)*/);
	CDB_green.WhenPressed(new ShooterSetFlywheelSpeed(SHOOT_CLOSE_HOPPER_RPM));
	CDB_bottomWhite.WhenPressed(new ShooterStartFlywheel());
	CDB_bottomRed.WhenPressed(new ShooterStopFlywheel());
}

double OI::GetTurn() {
	//gets forward/backward values
	return Desensitize(driverController.GetRawAxis(4));
}

double OI::GetMove() {
	//gets turning values
	if(InvertDriving()) {
		return Desensitize(driverController.GetRawAxis(1));
	}else{
		return Desensitize(driverController.GetRawAxis(1));
	}
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
	return Desensitize(coDriverController.GetRawAxis(2)) / 2;
}

double OI::GetTranslatedThrottle() {
		return ((-(coDriverController.GetAxis(frc::Joystick::AxisType::kThrottleAxis)) + 1) / 2);
}

