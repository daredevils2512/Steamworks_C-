#include "CompressorRun.h"

CompressorRun::CompressorRun() {

}
void CompressorRun::Initialize() {

}

void CompressorRun::Execute() {
	{
		//if the robot is not fully pressurized the compressor will turn on and run
		if(!Robot::compressor->Pressurized()) {
			Robot::compressor->On();
		}else{
			Robot::compressor->Off();
		}
	}

}

bool CompressorRun::IsFinished() {
	return false;
}

void CompressorRun::End() {

}

void CompressorRun::Interrupted() {

}
