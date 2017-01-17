#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include "WPILib.h"
#include "RobotMap.h"
#include "Commands/Command.h"
#include "LiveWindow/LiveWindow.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/CompressorSubsystem.h"
#include "OI.h"

class Robot : public IterativeRobot {
public:
	std::unique_ptr<Command> autonomousCommand;
	static std::unique_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();

static std::shared_ptr<Drivetrain> drivetrain;
static std::shared_ptr<CompressorSubsystem> compressor;

virtual void RobotInit();
virtual void DisabledInit();
virtual void DisabledPeriodic();
virtual void AutonomousInit();
virtual void AutonomousPeriodic();
virtual void TeleopInit();
virtual void TeleopPeriodic();
virtual void TestPeriodic();

private:
	bool chooser;
};
#endif
