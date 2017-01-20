#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include "WPILib.h"
#include "RobotMap.h"
#include "Commands/Command.h"
#include "LiveWindow/LiveWindow.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/CompressorSubsystem.h"
#include "Subsystems/Climber.h"
#include "OI.h"
//class declaration of the robot
class Robot : public IterativeRobot {
public:

	//pointer object declaration for subsystems, autonomous, oi, live window
	std::unique_ptr<Command> autonomousCommand;
	static std::unique_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();

static std::shared_ptr<Drivetrain> drivetrain;
static std::shared_ptr<CompressorSubsystem> compressor;
static std::shared_ptr<Climber> climber;

//declaration of robot class functions
virtual void RobotInit();
virtual void DisabledInit();
virtual void DisabledPeriodic();
virtual void AutonomousInit();
virtual void AutonomousPeriodic();
virtual void TeleopInit();
virtual void TeleopPeriodic();
virtual void TestPeriodic();

private:
	// true if using the autonomous chooser
	bool chooser;
};
#endif
