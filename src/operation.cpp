/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Source File: operation class implementation
****************************************************************************/

#include "../header/operation.h"

bool operation::is_compatible (const operation &op) const
{
	return type == op.type && ts != op.ts;
}