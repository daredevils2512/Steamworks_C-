#ifndef FloorIntakeRunMotor_H
#define FloorIntakeRunMotor_H

#include "../CommandBase.h"
#include "../Subsystems/FloorIntake.h"
#include "../Robot.h"

class FloorIntakeRunMotor : public CommandBase {
public:
	FloorIntakeRunMotor(double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	//makes a speed double
private:
	double m_speed;
};

#endif  // FloorIntakeRunMotor_H
