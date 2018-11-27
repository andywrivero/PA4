#ifndef RMUX_UNIT_H
#define RMUX_UNIT_H

#include <vector>
#include "mux_unit.h"
#include "reg_unit.h"
#include "fu_unit.h"

using std::vector;

struct rmux_unit : public mux_unit
{
	reg_unit *out;
	vector<fu_unit *> in;
};

#endif