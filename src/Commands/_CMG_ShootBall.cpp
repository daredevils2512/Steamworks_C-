#include "_CMG_ShootBall.h"
#include "ShooterRunSpinCycleFeed.h"
#include "ShooterRunFlywheel.h"
#include "PauseCommand.h"
#include "../Robot.h"

_CMG_ShootBall::_CMG_ShootBall() {
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
	AddSequential(new ShooterRunFlywheel(2490/*Robot::shooter->GetShooterSpeed()*/));//2050 for boiler shot; 2370 for hopper shot
	AddSequential(new PauseCommand(0.5));
	AddSequential(new ShooterRunSpinCycleFeed(0.8));
}
