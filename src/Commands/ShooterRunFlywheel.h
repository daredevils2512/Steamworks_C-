#ifndef ShooterRunFlywheel_H
#define ShooterRunFlywheel_H

#include "../CommandBase.h"
#include "CANTalon.h"
#include "Robot.h"

class ShooterRunFlywheel: public CommandBase {
public:
	ShooterRunFlywheel(double speed);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	double m_speed;
};

#endif
