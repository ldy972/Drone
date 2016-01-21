#ifndef SIM_REAL_H
#define SIM_REAL_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "navdata.h"
#include "shared.h"


#define D0 60.0
#define NB_MEASURES 36 

// Drone state inside the simulation : position in polar coordinates + heading
typedef struct _drone_state {
    float rho;
    float theta;
    float heading;
} drone_state;


int initialize_simulation();

void print_drone_state(FILE * out_file);

// Fills the array of simulated RSSI with the given direction for the direction of the target
void simulate_rssi(float target);
void update_sim(float distance, float direction);
float sim_get_pow(float theta);

int rotate_right_simu(int power, float heading_disp);
int forward_simu(int power, int times, float heading);
int orientate_simu(int power, float target_heading);
float get_simulated_heading();
float get_simulated_power();

int finish_simulation();


#endif
