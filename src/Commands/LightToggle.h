#ifndef LightToggle_H
#define LightToggle_H

#include "../CommandBase.h"

class LightToggle : public CommandBase {
public:
	LightToggle();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // LightToggle_H
