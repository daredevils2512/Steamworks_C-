#ifndef EXAMPLE_COMMAND_H
#define EXAMPLE_COMMAND_H

#include "../CommandBase.h"

class GearVisionScan: public CommandBase {
public:
	GearVisionScan(double targetX);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	double targetX;
};

#endif  // EXAMPLE_COMMAND_H
