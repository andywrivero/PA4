/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Source File: Edge class function implementation
****************************************************************************/

#include "../header/edge.h"

bool edge::is_compatible (const edge &e) const
{
	return !in_range(fw, e.fw, e.lr) && !in_range(e.fw, fw, lr);
}

bool edge::in_range (int a, int l, int h) const
{
	return a >= l && a < h;
}