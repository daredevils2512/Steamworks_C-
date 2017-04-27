#ifndef ShooterSetFlywheelSpeed_H
#define ShooterSetFlywheelSpeed_H

#include "../CommandBase.h"
#include "CANTalon.h"
#include "Robot.h"

class ShooterSetFlywheelSpeed: public CommandBase {
public:
	ShooterSetFlywheelSpeed(double speed);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	double m_speed;
};

#endif
