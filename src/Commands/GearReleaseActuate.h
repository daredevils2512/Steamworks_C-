#ifndef GearReleaseActuate_H
#define GearReleaseActuate_H

#include "../CommandBase.h"
#include "Robot.h"
class GearReleaseActuate : public CommandBase {
public:
	GearReleaseActuate(frc::DoubleSolenoid::Value SolenoidDirection);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	frc::DoubleSolenoid::Value m_SolenoidDirection;
};

#endif  // GearReleaseActuate_H
