#ifndef SIM_REAL_H
#define SIM_REAL_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "navdata.h"


#define D0 60.0
#define STEP 1
extern float* sim_rssi_array;

// Drone state inside the simulation : position in polar coordinates + heading
typedef struct _drone_state {
    float rho;
    float theta;
    float heading;
} drone_state;

// Fills the array of simulated RSSI with the given direction for the direction of the target
void simulate_rssi(float target);
void update_sim();
float sim_get_pow(float theta);

int rotate_right_simu(int power, float heading_disp);
int forward_simu(int power, int times, float heading);
float get_simulated_heading();
float get_simulated_power();



#endif
