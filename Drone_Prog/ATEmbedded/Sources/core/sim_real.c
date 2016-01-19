#include "sim_real.h"

drone_state state_howard;

int data_range = 360 / STEP;
float* sim_rssi_array = NULL;
float distance = D0; 
float x = 0; // distance à parcourir à 45°
float theta_max = 0; // cap de la plus grande puissance

int adjust_angle_i(int target)
{
    int adjusted_angle = target % 360;
    if (adjusted_angle < -180) {
        adjusted_angle += 360;
    } else if (adjusted_angle >= 180) {
        adjusted_angle -= 360;
    }

    return adjusted_angle;
}

int adjust_angle_f(float target)
{
    return adjust_angle_i((int) target);
}

void simulate_rssi(float target)
{
	int i = 0;
	int theta;
    	int base_orientation = adjust_angle_f(target);
	
	float power = 0;

    if (sim_rssi_array == NULL) {
        // Crée un tableau de 360 floats 
    	sim_rssi_array = malloc(sizeof(float) * data_range);
    }
    // puissance reçue en face de la cible en fonction de la distance
	
	for (i = 0; i < data_range; i++)
    {
        theta = i - base_orientation - 180;
        adjust_angle_i(theta);
        // calcul puissance
	power = -0.2255 * distance -14.527;
        power = (float) (-0.00017 * pow((double)theta, 2.0)+power);
        sim_rssi_array[i] = power;		
    }
}

void update_sim()
{
	x = 0.71 * distance; // computed thanks to drone velocity
	float heading = adjust_angle(state_howard.heading);
	float beta = adjust_angle(heading - pi + theta);
	
// computing the new polar position of the drone
	state_howard.rho = pow(state_howard.rho,2) + pow(x,2) +2*state_howard.rho*x*cos(beta);
	float gamma = adjust_angle(asin( sin(beta)*x/state_howard.rho;
	state_howard.theta = adjust_angle(adjust_angle(state_howard.theta) + gamma);

// updating drone heading depending on the mode used
	#ifndef FULL_SIMU
	state_howard.heading = adjust_angle(get_heading());
	#endif
	
	
	
}


float sim_get_pow(float theta)
{
	int index = (adjust_angle_f(theta)) + 180;
	return sim_rssi_array[index];
}


int rotate_right_simu(int power, float heading_disp)
{
    state_howard.heading += heading_disp;
    return 0;
}


int forward_simu(int power, int times, float heading)
{
    // Write function linking nb commands to distance
    return 0;
}


float get_simulated_heading()
{
    return state_howard.heading;
}


float get_simulated_power()
{
    return sim_rssi_array[adjust_angle_f(state_howard.heading)];
}
