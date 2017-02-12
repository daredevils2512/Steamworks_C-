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
	bool fwdLastPassed;
	bool revLastPassed;
	bool FwdEncPassedThisTime();
	bool RevEncPassedThisTime();
};

#endif  // EXAMPLE_COMMAND_H
