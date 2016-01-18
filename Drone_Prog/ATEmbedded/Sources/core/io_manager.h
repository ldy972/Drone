#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include "com_AT.h"
#include "navdata.h"
#include "sim_real.h"


#ifdef FULL_SIMU
#define POWER_SIMU
#endif

int turn_right(int power, float heading_disp);
int go_forward(int power, int times, float heading);
float retrieve_heading();
float retrieve_power();

#endif
