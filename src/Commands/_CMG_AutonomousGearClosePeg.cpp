#include <Commands/_CMG_AutonomousGearClosePeg.h>
#include <Commands/AutoCircleDrive.h>
#include "../Subsystems/Gear.h"
#include "../Subsystems/Drivetrain.h"
#include "AutoStraightDrive.h"
#include "AutoDimeSpin.h"
#include "../Robot.h"
#include "PauseCommand.h"
#include "GearGetLimitSwitch.h"
#include "ShooterSwivelTurret.h"
#include "ShooterVisionTrack.h"
#include "FloorIntakeRunMotor.h"
#include "_CMG_ShootBall.h"
#include "GearVisionTurn.h"
#include "ShooterSwivelMoveToPosition.h"
#include "ShooterSetFlywheelSpeed.h"
#include "_CMG_DiscountDoubleCheck.h"
#include "GearIntakeActuate.h"
#include "ShooterMoveHood.h"

_CMG_AutonomousGearClosePeg::_CMG_AutonomousGearClosePeg(bool gotoHopper) {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
//	AddSequential(new AutoCircleDrive(160.0, 1.0, Drivetrain::Direction::counterClockwise, 80.0));
	if(Robot::robotAlliance == frc::DriverStation::kBlue) {
//		AddSequential(new AutoStraightDrive(42.0, 0.7));
		AddParallel(new ShooterSwivelMoveToPosition(7800));
		AddSequential(new AutoStraightDrive(56.0, 0.7)); //62.0//64.0//62//56
		AddSequential(new PauseCommand(1.0));
		AddSequential(new AutoDimeSpin(0.9, 25.0, Robot::drivetrain->Direction::clockwise)); //15.0
		AddSequential(new PauseCommand(0.5));
//		AddSequential(new AutoStraightDrive(30.0, 0.7));//30
//		AddSequential(new PauseCommand(0.5));
		AddSequential(new GearVisionTurn(265));//210//200
		AddSequential(new PauseCommand(0.5));
//		AddSequential(new GearVisionTurn(265));
//		AddSequential(new PauseCommand(0.5));
//		AddSequential(new GearVisionTurn(265));
//		AddSequential(new PauseCommand(0.2));
		AddSequential(new AutoStraightDrive(23.0, 0.55));
		AddSequential(new GearIntakeActuate(frc::DoubleSolenoid::Value::kForward));
		AddSequential(new ShooterMoveHood(frc::DoubleSolenoid::Value::kForward));
		AddSequential(new ShooterVisionTrack(true));
		AddSequential(new ShooterSetFlywheelSpeed(4250));//4120
		AddSequential(new _CMG_ShootBall());
		AddSequential(new PauseCommand(3.0));
		AddSequential(new _CMG_DiscountDoubleCheck());
		if(gotoHopper) {
			AddSequential(new GearGetLimitSwitch());
			AddSequential(new PauseCommand(1.0));
			AddParallel(new ShooterSwivelTurret(-0.4));
			AddSequential(new AutoStraightDrive(25.0, -0.7));
			AddSequential(new ShooterSwivelTurret(0.0));
			AddSequential(new PauseCommand(0.2));
			AddSequential(new AutoDimeSpin(0.9, 47.0, Robot::drivetrain->Direction::counterClockwise));
			AddSequential(new PauseCommand(0.2));
			AddSequential(new AutoStraightDrive(44.0, 0.9));
			AddSequential(new PauseCommand(0.5));
			AddSequential(new ShooterVisionTrack(true));
			AddParallel(new FloorIntakeRunMotor(-1.0));
			AddSequential(new _CMG_ShootBall());
		}
	}else{//red
//		AddSequential(new AutoStraightDrive(42.0, 0.7));//34
		AddParallel(new ShooterSwivelMoveToPosition(-8000));
		AddSequential(new AutoStraightDrive(56.0, 0.7)); //62.0
		AddSequential(new PauseCommand(1.0));
		AddSequential(new AutoDimeSpin(0.9, 25.0, Robot::drivetrain->Direction::counterClockwise));
		AddSequential(new PauseCommand(0.5));
//		AddSequential(new AutoStraightDrive(30.0, 0.7));//30
//		AddSequential(new PauseCommand(0.5));
		AddSequential(new GearVisionTurn(265)); //200
		AddSequential(new PauseCommand(0.5));
//		AddSequential(new GearVisionTurn(265));
//		AddSequential(new PauseCommand(0.5));
//		AddSequential(new GearVisionTurn(265));
//		AddSequential(new PauseCommand(0.2));
		AddSequential(new AutoStraightDrive(23.0, 0.55));
		AddSequential(new GearIntakeActuate(frc::DoubleSolenoid::Value::kForward));
		AddSequential(new ShooterMoveHood(frc::DoubleSolenoid::Value::kForward));
		AddSequential(new ShooterVisionTrack(true));
		AddSequential(new ShooterSetFlywheelSpeed(4220));//4085//4120
		AddSequential(new _CMG_ShootBall());
		AddSequential(new PauseCommand(3.0));
		AddSequential(new _CMG_DiscountDoubleCheck());
		if(gotoHopper) {
			AddSequential(new GearGetLimitSwitch());
			AddSequential(new PauseCommand(1.0));
			AddParallel(new ShooterSwivelTurret(0.4));
			AddSequential(new AutoStraightDrive(25.0, -0.7));
			AddSequential(new ShooterSwivelTurret(0.0));
			AddSequential(new PauseCommand(0.2));
			AddSequential(new AutoDimeSpin(0.9, 47.0, Robot::drivetrain->Direction::clockwise));
			AddSequential(new PauseCommand(0.2));
			AddSequential(new AutoStraightDrive(44.0, 0.9));
			AddSequential(new PauseCommand(0.5));
			AddSequential(new ShooterVisionTrack(true));
			AddParallel(new FloorIntakeRunMotor(-1.0));
			AddSequential(new _CMG_ShootBall());
		}
	}
}
