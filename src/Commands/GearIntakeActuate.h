#ifndef GearIntakeActuate_H
#define GearIntakeActuate_H

#include "../CommandBase.h"
#include "Robot.h"
class GearIntakeActuate : public CommandBase {
public:
	GearIntakeActuate(frc::DoubleSolenoid::Value SolenoidDirection);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	frc::DoubleSolenoid::Value m_SolenoidDirection;
};

#endif  // GearIntakeActuate_H
