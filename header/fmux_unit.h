#ifndef FMUX_UNIT_H
#define FMUX_UNIT_H

#include <vector>
#include "mux_unit.h"
#include "reg_unit.h"
#include "fu_unit.h"

using std::vector;

struct fmux_unit : public mux_unit
{
	fu_unit *out;
	vector<reg_unit *> in;
};

#endif