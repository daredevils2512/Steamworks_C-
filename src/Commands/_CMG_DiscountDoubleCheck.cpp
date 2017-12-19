#include "_CMG_DiscountDoubleCheck.h"
#include "PauseCommand.h"
#include "GearGetLimitSwitch.h"
#include "AutoStraightDrive.h"
#include "GearVisionTurn.h"

_CMG_DiscountDoubleCheck::_CMG_DiscountDoubleCheck() {
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
	if(Robot::gear->GetLimitSwitch()){
		std::cout << "discount double check" << std::endl;
		AddSequential(new AutoStraightDrive(8.0, -0.5));
		AddSequential(new PauseCommand(0.5));
		AddSequential(new GearVisionTurn(210));
		AddSequential(new PauseCommand(0.5));
		AddSequential(new GearVisionTurn(210));
		AddSequential(new PauseCommand(0.5));
		AddSequential(new GearVisionTurn(210));
		AddSequential(new PauseCommand(0.2));
		AddSequential(new AutoStraightDrive(8.0, 0.5));
	}

}
