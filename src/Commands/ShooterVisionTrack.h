#ifndef EXAMPLE_COMMAND_H
#define EXAMPLE_COMMAND_H

#include "../CommandBase.h"

class ShooterVisionTrack: public CommandBase {
public:
	ShooterVisionTrack();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
