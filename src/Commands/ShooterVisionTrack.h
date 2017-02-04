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
};

#endif  // ShooterVisionTrack_H
