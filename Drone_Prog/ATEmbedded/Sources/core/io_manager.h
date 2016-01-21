#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include "com_AT.h"
#include "navdata.h"
#include "sim_real.h"
#include "shared.h"

#if defined FULL_SIMU || defined POWER_SIMU
#define SIMU
#endif

int turn_right(int power, float heading_disp);
int go_forward(int power, int times, float heading);
int orientate_drone(int power, float target_heading);
float retrieve_heading();
float retrieve_power();
trajectory_measure_t get_max_measure(trajectory_measure_t *measure);
trajectory_measure_t get_max_power_measure();

#endif
