#ifndef ShooterRunBoosters_Watchdog_H
#define ShooterRunBoosters_Watchdog_H

#include "../CommandBase.h"
#include "CANTalon.h"
#include "Robot.h"

class ShooterRunBoosters_Watchdog : public CommandBase {
public:
	ShooterRunBoosters_Watchdog(double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double m_speed;
};

#endif  // ShooterRunBoosters_Watchdog_H
