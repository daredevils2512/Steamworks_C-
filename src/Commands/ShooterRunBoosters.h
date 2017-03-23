#ifndef ShooterRunBoosters_H
#define ShooterRunBoosters_H

#include "../CommandBase.h"
#include "CANTalon.h"
#include "Robot.h"

class ShooterRunBoosters : public CommandBase {
public:
	ShooterRunBoosters(double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double m_speed;
};

#endif  // ShooterRunBoosters_H
