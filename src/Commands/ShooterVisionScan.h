#ifndef EXAMPLE_COMMAND_H
#define EXAMPLE_COMMAND_H

#include "../CommandBase.h"

class ShooterVisionScan: public CommandBase {
public:
	ShooterVisionScan();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	double speed;
	bool fwdLastPressed;
	bool revLastPressed;
	bool FwdPressedThisTime();
	bool RevPressedThisTime();
};

#endif  // EXAMPLE_COMMAND_H
