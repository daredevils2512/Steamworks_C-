#ifndef DrivetrainShift_H
#define DrivetrainShift_H

#include "../CommandBase.h"
#include "Robot.h"

class DrivetrainShift : public CommandBase {
public:
	DrivetrainShift(bool Direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_Direction;
};

#endif  // DrivetrainShift_H
