#include "../header/operation.h"

bool operation::is_compatible (const operation &op) const
{
	return type == op.type && ts != op.ts;
}