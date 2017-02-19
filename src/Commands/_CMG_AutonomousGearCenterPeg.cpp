#include <Commands/_CMG_AutonomousGearCenterPeg.h>
#include <Commands/AutoStraightDrive.h>
#include "GearGetLimitSwitch.h"
#include "PauseCommand.h"
#include "GearGetLimitSwitch.h"
#include "PauseCommand.h"
#include "../Subsystems/Drivetrain.h"

_CMG_AutonomousGearCenterPeg::_CMG_AutonomousGearCenterPeg() {
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
	Robot::drivetrain->ResetEncoders();
	AddSequential(new AutoStraightDrive(9.4, 1.0));
	AddSequential(new GearGetLimitSwitch());
	AddSequential(new PauseCommand(1.0));
	AddSequential(new AutoStraightDrive(0.75, -1.0));
}
