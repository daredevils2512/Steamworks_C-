#include "_CMG_AutonomousHopper.h"
#include "PauseCommand.h"
#include "AutoDimeSpin.h"
#include "AutoStraightDrive.h"
#include "ShooterVisionTrack.h"
#include "_CMG_ShootBall.h"
#include "ShooterSwivelTurret.h"
#include "FloorIntakeRunMotor.h"
#include "ShooterRunSpinCycleFeed.h"

_CMG_AutonomousHopper::_CMG_AutonomousHopper() {
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
	AddParallel(new ShooterSwivelTurret(-0.4));
	AddSequential(new AutoStraightDrive(50.0, 0.7));
	AddSequential(new ShooterSwivelTurret(0.0));
	AddSequential(new PauseCommand(0.2));
	AddSequential(new AutoDimeSpin(0.9, 33.0, Robot::drivetrain->Direction::counterClockwise));
	AddSequential(new PauseCommand(0.2));
	AddSequential(new AutoStraightDrive(20.0, 0.7));
	AddParallel(new ShooterVisionTrack(true));
	AddParallel(new FloorIntakeRunMotor(-1.0));
	AddSequential(new _CMG_ShootBall());
//	AddSequential(new PauseCommand(2.0));
//	AddSequential(new ShooterRunSpinCycleFeed(-0.95));
//	AddSequential(new PauseCommand(0.5));
//	AddSequential(new ShooterRunSpinCycleFeed(0.95));
//
//	AddSequential(new PauseCommand(2.0));
//	AddSequential(new ShooterRunSpinCycleFeed(-0.95));
//	AddSequential(new PauseCommand(0.5));
//	AddSequential(new ShooterRunSpinCycleFeed(0.95));
//
//	AddSequential(new PauseCommand(2.0));
//	AddSequential(new ShooterRunSpinCycleFeed(-0.95));
//	AddSequential(new PauseCommand(0.5));
//	AddSequential(new ShooterRunSpinCycleFeed(0.95));
//
//	AddSequential(new PauseCommand(2.0));
//	AddSequential(new ShooterRunSpinCycleFeed(-0.95));
//	AddSequential(new PauseCommand(0.5));
//	AddSequential(new ShooterRunSpinCycleFeed(0.95));
}
