#ifndef ShooterVisionTrack_H
#define ShooterVisionTrack_H

#include "../CommandBase.h"

class ShooterVisionTrack: public CommandBase {
public:
	ShooterVisionTrack();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	bool IsWithinThreshold(double setpoint, double threshold, double value);
	bool abort;
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

#endif  // ShooterVisionTrack_H
