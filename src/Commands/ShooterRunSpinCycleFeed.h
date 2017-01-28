#ifndef ShooterRunSpinCycleFeed_H
#define ShooterRunSpinCycleFeed_H

#include "../CommandBase.h"
#include "CANTalon.h"
#include "Robot.h"

class ShooterRunSpinCycleFeed: public CommandBase {
public:
	ShooterRunSpinCycleFeed(double speed);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	double m_speed;
};

#endif
