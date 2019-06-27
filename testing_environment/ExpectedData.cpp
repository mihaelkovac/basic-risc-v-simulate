#include "ExpectedData.h"

bool ExpectedData::empty() const noexcept
{
	return this->registers.empty() && this->memory_locations.empty() && !pc;
}
