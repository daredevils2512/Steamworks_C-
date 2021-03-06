#include <Commands/_CMG_AutonomousGearCenterPeg.h>
#include <Commands/AutoStraightDrive.h>
#include "GearGetLimitSwitch.h"
#include "PauseCommand.h"
#include "../Subsystems/Drivetrain.h"
#include "GearVisionTurn.h"
#include "_CMG_ShootBall_BoosterWatchdog.h"


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
//	AddSequential(new AutoStraightDrive(48.0, 0.7));
//	AddSequential(new GearIntakeActuate(frc::DoubleSolenoid::kReverse));
	AddSequential(new AutoStraightDrive(31.0, 0.7)); //30//0.7
	AddSequential(new PauseCommand(0.75));
//	AddSequential(new GearVisionTurn(265));//208//210//200
//	AddSequential(new PauseCommand(0.2));
//	AddSequential(new GearVisionTurn(265));
//	AddSequential(new PauseCommand(0.2));
//	AddSequential(new GearVisionTurn(265));
//	AddSequential(new PauseCommand(0.2));
	AddSequential(new AutoStraightDrive(20.0, 0.55)); //20.0
	AddSequential(new _CMG_ShootBall_BoosterWatchdog());
}
