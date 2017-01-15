#ifndef DRIVE_H
#define DRIVE_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class Drive: public Command {
public:
	Drive(double move , double turn);

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	double m_move;
	double m_turn;
};

#endif
