#include <Commands/AutoCircleDrive.h>
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
#include "Commands/ShooterPOVHoodControl.h"
#include "Commands/SetShootBallSpeed.h"
#include "Commands/_CMG_ShooterManualSwivel.h"
#include "Commands/GearToggleIntake.h"


OI::OI()
{
	// activates commands here based off of operator input
	DRC_rightTrigger.WhenPressed(new DrivetrainShift(true));//working
	DRC_rightTrigger.WhenReleased(new DrivetrainShift(false));//working
	DRC_rightBumper.WhenPressed(new FloorIntakeRunMotor(-1.0));//working
	DRC_leftBumper.WhenPressed(new FloorIntakeRunMotor(0.0));//working
	DRC_xButton.WhileHeld(new ClimberRunMotor(0.8));//working
	DRC_xButton.WhenReleased(new ClimberRunMotor(0.0));//working
//	DRC_yButton.WhileHeld(new ClimberRunMotor(0.8));//working
//	DRC_yButton.WhenReleased(new ClimberRunMotor(0.0));//working
	DRC_yButton.WhileHeld(new FloorIntakeRunMotor(1.0));//working
	DRC_yButton.WhenReleased(new FloorIntakeRunMotor(0.0));//working
	DRC_aButton.WhenPressed(new GearIntakeActuate(frc::DoubleSolenoid::kForward));//working
	DRC_bButton.WhenPressed(new GearIntakeActuate(frc::DoubleSolenoid::kReverse));//working

	CDR_trigger.WhileHeld(new _CMG_ShootBall());//working
	CDR_trigger.WhenReleased(new ShooterRunFlywheel(0.0));//working
	CDR_trigger.WhenReleased(new ShooterRunSpinCycleFeed(0.0));//working
	CDR_joystickPOV.WhenPressed(new ShooterPOVHoodControl());//working
	CDR_sideJoystickButton.WhileHeld(new ShooterVisionTrack());//working
	CDR_topLeftJoystick.WhileHeld(new FloorIntakeRunMotor(-1.0));//working
	CDR_topLeftJoystick.WhenReleased(new FloorIntakeRunMotor(0.0));//working
//	CDR_bottomLeftJoystick.WhenPressed(new GearIntakeActuate(frc::DoubleSolenoid::kReverse));//working
//	CDR_bottomLeftJoystick.WhenReleased(new GearIntakeActuate(frc::DoubleSolenoid::kForward));//working
	CDR_bottomLeftJoystick.WhenPressed(new GearToggleIntake());
	CDR_topRightJoystick.WhileHeld(new ClimberRunMotor(0.8));//working
	CDR_topRightJoystick.WhenReleased(new ClimberRunMotor(0.0));//working
	CDR_bottomRightJoystick.WhileHeld(new ClimberRunMotor(-0.8));//working
	CDR_bottomRightJoystick.WhenReleased(new ClimberRunMotor(0.0));//working
//	CDR_bottomRightBase.WhenPressed(new ShooterRunFlywheel(0.4));//working
//	CDR_topRightBase.WhenPressed(new ShooterRunFlywheel(2570));//working
	CDR_bottomRightBase.WhenPressed(new SetShootBallSpeed(2250));
	CDR_topRightBase.WhenPressed(new SetShootBallSpeed(2400));
	CDR_bottomLeftBase.WhenPressed(new ShooterRunSpinCycleFeed(0.8));//working
	CDR_topLeftBase.WhenPressed(new ShooterRunSpinCycleFeed(0.0));//working
	CDR_topMiddleBase.WhenPressed(new ShooterRunFlywheel(0.0));//working, sometimes wheels spurt randomly
	CDR_zPositiveAxis.WhileHeld(new ShooterManualSwivel());//working
	CDR_zPositiveAxis.WhenReleased(new ShooterSwivelTurret(0.0));//working
	CDR_zNegativeAxis.WhileHeld(new ShooterManualSwivel());//working
	CDR_zNegativeAxis.WhenReleased(new ShooterSwivelTurret(0.0));//working
	CDR_throttle.WhileHeld(new ShooterManualRunFlywheel());//working
	CDR_throttle.WhenReleased(new ShooterRunFlywheel(0.0));//working

	CDB_bigWhite.WhenPressed(new ShooterMoveHood(frc::DoubleSolenoid::kForward));//working
	CDB_bigRed.WhenPressed(new ShooterMoveHood(frc::DoubleSolenoid::kReverse));//working
	CDB_green.WhileHeld(new FloorIntakeRunMotor(1.0));//working
	CDB_green.WhenReleased(new FloorIntakeRunMotor(0.0));//working
//	CDB_yellow.WhenPressed(new GearIntakeActuate(frc::DoubleSolenoid::kReverse));//working
//	CDB_yellow.WhenReleased(new GearIntakeActuate(frc::DoubleSolenoid::kForward));//working
	CDB_yellow.WhenPressed(new AutoCircleDrive(36.0, 0.5, Robot::drivetrain->Direction::clockwise, 90.0)); //90
	CDB_bottomWhite.WhileHeld(new ClimberRunMotor(0.8));//working
	CDB_bottomWhite.WhenReleased(new ClimberRunMotor(0.0));//working
	CDB_bottomRed.WhileHeld(new ClimberRunMotor(-0.8));//working
	CDB_bottomRed.WhenReleased(new ClimberRunMotor(0.0));//working
//	CDB_topWhite.WhenPressed(new ShooterRunFlywheel(0.6));//working
//	CDB_topRed.WhenPressed(new ShooterRunFlywheel(0.8));//working
	CDB_topWhite.WhenPressed(new SetShootBallSpeed(2250));
	CDB_topRed.WhenPressed(new SetShootBallSpeed(2400));
//	CDB_middleWhite.WhileHeld(new ShooterSwivelTurret(1.0));//working
//	CDB_middleWhite.WhenReleased(new ShooterSwivelTurret(0.0));//working
//	CDB_middleRed.WhileHeld(new ShooterSwivelTurret(-1.0));//working
//	CDB_middleRed.WhenReleased(new ShooterSwivelTurret(0.0));//working
	CDB_middleWhite.WhenPressed(new _CMG_ShooterManualSwivel(1.0));
	CDB_middleRed.WhenPressed(new _CMG_ShooterManualSwivel(-1.0));
}

double OI::GetTurn() {
	//gets forward/backward values
	return Desensitize(-driverController.GetRawAxis(4));
}

double OI::GetMove() {
	//gets turning values
	if(InvertDriving()) {
		return Desensitize(driverController.GetRawAxis(1));
	}else{
		return Desensitize(-driverController.GetRawAxis(1));
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
	return Desensitize(coDriverController.GetRawAxis(2));
}

double OI::GetTranslatedThrottle() {
		return ((-(coDriverController.GetAxis(frc::Joystick::AxisType::kThrottleAxis)) + 1) / 2) * 3000;
}

