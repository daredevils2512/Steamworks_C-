#ifndef ClimberRunMotor_H
#define ClimberRunMotor_H

#include "../CommandBase.h"
#include "../Subsystems/Climber.h"
#include "../Robot.h"

class ClimberRunMotor : public CommandBase {
public:
	ClimberRunMotor(double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	//creating a double to store the speed inputed
	double m_speed;
};

#endif  // ClimberRunMotor_H
