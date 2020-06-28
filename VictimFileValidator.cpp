#include "VictimFileValidator.h"

void VictimFileValidator::ValidateVictimFile(const VictimFile& victimFile) {
	if (victimFile.getAge() < 0)
		throw ValidationException("The age can not be negative\n");
	if (victimFile.getName().empty())
		throw ValidationException("The name can not be empty\n");
}
