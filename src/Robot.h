#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include "WPILib.h"
#include "RobotMap.h"
#include "Commands/Command.h"
#include "LiveWindow/LiveWindow.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/Climber.h"
#include "Subsystems/FloorIntake.h"
#include "Subsystems/Gear.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/PixySubsystem.h"
#include "Commands/GearIntakeActuate.h"
#include "OI.h"
#include "FileIO.h"

//class declaration of the robot
class Robot : public IterativeRobot {
public:

	//pointer object declaration for subsystems, autonomous, oi, live window
	std::unique_ptr<frc::CommandGroup> autonomousCommand;
	static std::unique_ptr<OI> oi;
	static frc::DriverStation::Alliance robotAlliance;


static std::shared_ptr<Drivetrain> drivetrain;
static std::shared_ptr<Climber> climber;
static std::shared_ptr<FloorIntake> floorIntake;
static std::shared_ptr<Gear> gear;
static std::shared_ptr<Shooter> shooter;
static std::shared_ptr<PixySubsystem> pixySubsystem;

static std::shared_ptr<frc::Compressor> compressor;

//declaration of robot class functions
virtual void RobotInit();
virtual void DisabledInit();
virtual void DisabledPeriodic();
virtual void AutonomousInit();
virtual void AutonomousPeriodic();
virtual void TeleopInit();
virtual void TeleopPeriodic();
virtual void TestPeriodic();
};
#endif
