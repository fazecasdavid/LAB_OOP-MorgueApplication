#pragma once
#include "VictimFile.h"
#include "exceptions.h"


class VictimFileValidator {
public:
	void static ValidateVictimFile(const VictimFile& victimFile);
};

