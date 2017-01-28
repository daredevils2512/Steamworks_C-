#ifndef ShooterMoveHood_H
#define ShooterMoveHood_H

#include "../CommandBase.h"
#include "CANTalon.h"
#include "Robot.h"

class ShooterMoveHood: public CommandBase {
public:
	ShooterMoveHood(frc::DoubleSolenoid::Value direction);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	frc::DoubleSolenoid::Value m_direction;
};

#endif
