#include "_CMG_GearCenterPeg.h"
#include "AutoDrive.h"
#include "GearGetLimitSwitch.h"
#include "PauseCommand.h"

_CMG_GearCenterPeg::_CMG_GearCenterPeg() {
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
	AddSequential(new AutoDrive(1.0, 0.347, Drivetrain::Direction::straight, 112.0, 0.0));
	AddSequential(new GearGetLimitSwitch());
	AddSequential(new PauseCommand(1.0));
	AddSequential(new AutoDrive(1.0, -0.347, Drivetrain::Direction::straight, 8.5, 0.0));
}