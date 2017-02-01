#include "Gear.h"
#include "../RobotMap.h"

Gear::Gear() : Subsystem("Gear") {
	limitswitch = RobotMap::gearLimitSwitch;
	photoeye = RobotMap::gearPhotoeye;
	solenoid = RobotMap::gearSolenoid;

	pixyCamera = RobotMap::gearPixy;
}

void Gear::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

bool Gear::GetLimitSwitch() {
	return limitswitch->Get();
}

bool Gear::GetPhotoeye() {
	return photoeye->Get();
}

void Gear::ActuateGearIntake(frc::DoubleSolenoid:: Value dir) {
	solenoid->Set(dir);
}

void Gear::UpdateObjectData() {
	pixyCamera->CollectFrameData();
}

bool Gear::ObjectExists(Nullable< std::vector<int> > object) {
	return (object.HasValue() && !pixyCamera->IsFrameEmpty());
}

Nullable< std::vector<int> > Gear::GetObjectData(int objectIndex) {
	targetObject = pixyCamera->GetObjectData(objectIndex);
	if(ObjectExists(targetObject)) {
		return Nullable< std::vector<int> >(targetObject.GetValue());
	}else{
		return Nullable< std::vector<int> >();
	}
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
