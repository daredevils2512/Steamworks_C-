#ifndef ShooterSwivelTurret_H
#define ShooterSwivelTurret_H

#include "../CommandBase.h"
#include "CANTalon.h"
#include "Robot.h"

class ShooterSwivelTurret: public CommandBase {
public:
	ShooterSwivelTurret(double speed);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	double m_speed;
};

#endif
