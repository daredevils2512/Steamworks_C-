#ifndef ShooterStopFlywheel_H
#define ShooterStopFlywheel_H

#include "../CommandBase.h"
#include "CANTalon.h"
#include "Robot.h"

class ShooterStopFlywheel: public CommandBase {
public:
	ShooterStopFlywheel();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
};

#endif
