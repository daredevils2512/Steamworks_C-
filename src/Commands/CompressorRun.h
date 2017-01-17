#ifndef CompressorRun_H
#define CompressorRun_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "Commands/Subsystem.h"
#include "../Robot.h"

class CompressorRun : public CommandBase {
public:
	CompressorRun();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CompressorRun_H
