#include <Commands/_CMG_AutonomousGearClosePeg.h>
#include <Commands/AutoCircleDrive.h>
#include "../Subsystems/Gear.h"
#include "../Subsystems/Drivetrain.h"
#include "AutoStraightDrive.h"
#include "AutoDimeSpin.h"
#include "../Robot.h"
#include "PauseCommand.h"
#include "GearIntakeActuate.h"

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
	AddSequential(new AutoStraightDrive(44.0, 0.7));
	AddSequential(new PauseCommand(0.2));
	AddSequential(new AutoDimeSpin(0.9, 19.0, Robot::drivetrain->Direction::clockwise));
	AddSequential(new PauseCommand(0.2));
	AddSequential(new AutoStraightDrive(44.0, 0.7));
	AddSequential(new GearIntakeActuate(frc::DoubleSolenoid::kReverse));
}
