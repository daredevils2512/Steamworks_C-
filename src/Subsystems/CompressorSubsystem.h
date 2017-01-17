#ifndef Compressor_H
#define Compressor_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class CompressorSubsystem: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	std::shared_ptr<Relay> spike;
	std::shared_ptr<DigitalInput> pressureSwitch;
	CompressorSubsystem();
	void InitDefaultCommand();
	void On();
	void Off();
	bool Pressurized();
};

#endif
