#ifndef SIM_REAL_H
#define SIM_REAL_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "navdata.h"


#define D0 60.0
#define STEP 1
extern float* sim_rssi_array;


// Fills the array of simulated RSSI with the given direction for the direction of the target
void simulate_rssi(float target);
void update_sim();
float sim_get_pow(float theta);



#endif
