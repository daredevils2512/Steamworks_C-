#include "_CMG_ShootBall_BoosterWatchdog.h"
#include "ShooterRunSpinCycleFeed.h"
#include "ShooterRunFlywheel.h"
#include "PauseCommand.h"
#include "../Robot.h"
#include "ShooterRunBoosters_Watchdog.h"
#include "ShooterStartFlywheel.h"
#include "ShooterSetFlywheelSpeed.h"

_CMG_ShootBall_BoosterWatchdog::_CMG_ShootBall_BoosterWatchdog() {
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
	AddSequential(new ShooterSetFlywheelSpeed(6100));
	AddSequential(new ShooterStartFlywheel());//6100; 4200
	AddSequential(new PauseCommand(0.5));
	AddParallel(new ShooterRunBoosters_Watchdog(0.75));
	AddSequential(new ShooterRunSpinCycleFeed(0.8));
}
