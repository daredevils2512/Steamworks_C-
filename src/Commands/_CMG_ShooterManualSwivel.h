#ifndef _CMG_ShooterManualSwivel_H
#define _CMG_ShooterManualSwivel_H

#include <Commands/CommandGroup.h>

class _CMG_ShooterManualSwivel : public CommandGroup {
public:
	_CMG_ShooterManualSwivel(double speed);
};

#endif  // _CMG_ShooterManualSwivel_H
