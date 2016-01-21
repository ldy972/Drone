#include "sim_real.h"

/******************************************************************************
 * Global Variables                                                           *
 *****************************************************************************/

drone_state state_howard;

FILE * simulation_output;
int data_step = 360 / NB_MEASURES;
trajectory_measure_t * sim_rssi_array = NULL;
float x = 0; // distance à parcourir à 45°
float theta_max = 0; // cap de la plus grande puissance
float to_rad = M_PI / 180.0;

/******************************************************************************
 * Local functions prototypes                                                 *
 *****************************************************************************/

int adjust_angle_i(int target);
int adjust_angle_f(float target);
float compute_travelled_distance(int times);

/******************************************************************************
 * Local functions declarations                                               *
 *****************************************************************************/

int adjust_angle_i(int target)
{
    int adjusted_angle = target % 360;
    if (adjusted_angle < 0) {
        adjusted_angle += 360;
    }
    return adjusted_angle;
}


int adjust_angle_f(float target)
{
    return adjust_angle_i((int) target);
}

float compute_travelled_distance(int times)
{
    return 0.0006 * pow((float)times, 2.0) + 0.0645 * (float)times - 0.1443;
}

/******************************************************************************
 * Functions declarations                                                     *
 *****************************************************************************/

int initialize_simulation()
{
    simulation_output = fopen("simulation_output.csv", "w");

    if (simulation_output == NULL) {
        fprintf(stderr, "Error opening output file for simulation\n");
        return 1;
    }

    state_howard.rho = D0;
    state_howard.theta = 0.0;
    state_howard.heading = 180.0;

    simulate_rssi(state_howard.heading);

    print_drone_state(stdout);

    return 0;
}

void print_drone_state(FILE * out_file)
{
    if(out_file != NULL) {
        fprintf(out_file, "%f, %f, %f\n", state_howard.rho, state_howard.theta, state_howard.heading);
    }
}

void print_rssi_array(FILE * out_file)
{
    int i;
    for (i = 0; i < data_step; i++) {
        fprintf(out_file, "%f,%f;", sim_rssi_array[i].cap, sim_rssi_array[i].power);
    }
    fprintf(out_file, "\n");
}

void simulate_rssi(float target)
{
	int i = 0;
    int base_orientation = adjust_angle_f(state_howard.theta - 180.0);
	
	float power = 0;

    if (sim_rssi_array == NULL) {
        // Crée un tableau de 360 floats 
    	sim_rssi_array = malloc(sizeof(trajectory_measure_t) * NB_MEASURES);
    }
    // puissance reçue en face de la cible en fonction de la distance
	
	for (i = 0; i < NB_MEASURES; i ++)
    {
	    int current_simulated_signal;
        current_simulated_signal = (i * data_step - base_orientation) % 360;
        if (current_simulated_signal < -180) {
            current_simulated_signal += 360; 
        } else if (current_simulated_signal > 180) {
            current_simulated_signal -= 360; 
        }
        // calcul puissance
    	power = -0.2255 * state_howard.rho - 14.527;
        power = (float) (-0.00017 * pow((double)current_simulated_signal, 2.0)+power);
        sim_rssi_array[i].power = power;		
    }

    print_rssi_array(stdout);
}

void update_sim(float distance, float direction)
{
    printf("[SIM] Move %fm in direction %f\n", distance, direction);
	float heading = (float) adjust_angle_f(state_howard.heading);
	float beta = (float) adjust_angle_f(heading - 180.0 + state_howard.theta);
	
    // computing the new polar position of the drone
	state_howard.rho = sqrt(pow(state_howard.rho,2) + pow(distance,2) - 2*state_howard.rho*distance*cos(beta * to_rad));
	float gamma = (float) adjust_angle_f(asin(sin(beta * to_rad) * distance / state_howard.rho) / to_rad);
	state_howard.theta = (float) adjust_angle_f(state_howard.theta + gamma);

    print_drone_state(stdout);

    // updating drone heading depending on the mode used
	#ifndef FULL_SIMU
	state_howard.heading = (float) adjust_angle_f(get_heading());
	#endif
}


float sim_get_pow(float theta)
{
	int index = (adjust_angle_f(theta)) + 180;
	return sim_rssi_array[index].power;
}


int rotate_right_simu(int power, float heading_disp)
{
    int result = 0;
#ifdef FULL_SIMU
    printf("[SIM] Rotate\n");
    state_howard.heading += heading_disp;
#else
    result = rotate_right_mag(power, heading_disp);
    state_howard.heading = get_heading();
#endif
    print_drone_state(simulation_output);
    return result;
}

int forward_simu(int power, int times, float heading)
{
    int result = 0;
#ifdef FULL_SIMU
    printf("[SIM] Forward\n");
    // When the drone is simulated, calculate its position and update state
    update_sim(compute_travelled_distance(times), heading);
    simulate_rssi((float) adjust_angle_f(state_howard.theta - 180.0));
#else
    // When the drone is not simulated, make it move and get its heading
    result = forward_mag(power, times, heading);
    state_howard.heading = get_heading();
#endif
    print_drone_state(simulation_output);
    return result;
}


int orientate_simu(int power, float target_heading)
{
    int result = 0;
#ifdef FULL_SIMU
    printf("[SIM] Orientate towards %f\n", target_heading);
    int turns = (int) state_howard.heading / 360;
    
    if (state_howard.heading < 0.0) {
        turns --;
    }

    state_howard.heading = (float) adjust_angle_f(target_heading) + 360.0 * turns;
#else
    // When the drone is not simulated, make it move and get its heading
    result = orientate_mag(power, target_heading);
    state_howard.heading = get_heading();
#endif
    print_drone_state(simulation_output);
    return result;

}

float get_simulated_heading()
{
#ifdef FULL_SIMU
    //printf("[SIM] Get heading\n");
    return state_howard.heading;
#else
    return get_heading();
#endif
}


float get_simulated_power()
{
    //printf("[SIM] Get power\n");
    return sim_rssi_array[adjust_angle_f(state_howard.heading)].power;
}


trajectory_measure_t get_max_simulated_measure()
{
    trajectory_measure_t max_measure;
    max_measure.power = FLT_MIN;

    int i;
    for (i = 0; i < NB_MEASURES; i++){
        if (max_measure.power < sim_rssi_array[i].power) {
            max_measure = sim_rssi_array[i];
        }
    }

    return max_measure;
}

int finish_simulation()
{
    free(sim_rssi_array);
    if(fclose(simulation_output) != 0){
        fprintf(stderr, "Error closing simulation file\n");
        return 1;
    }

    return 0;
}
