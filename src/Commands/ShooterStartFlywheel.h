#ifndef ShooterStartFlywheel_H
#define ShooterStartFlywheel_H

#include "../CommandBase.h"
#include "CANTalon.h"
#include "Robot.h"

class ShooterStartFlywheel: public CommandBase {
public:
	ShooterStartFlywheel();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
};

#endif
