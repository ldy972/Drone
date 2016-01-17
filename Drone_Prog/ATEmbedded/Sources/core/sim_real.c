#include "sim_real.h"


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
	float attenuation = 0.0;
	float power = 0;

    if (sim_rssi_array == NULL) {
        // Crée un tableau de 360 floats 
    	sim_rssi_array = malloc(sizeof(float) * data_range);
    }
    // puissance reçue en face de la cible en fonction de la distance
	power = -0.2255 * distance -14.527;
	for (i = 0; i < data_range; i++)
    {
        theta = i - base_orientation - 180;
        adjust_angle_i(theta);
        // coeff d'atténuation de puissance en fonction de l'angle
        attenuation = (float) (-3.0 * pow(10.0, -5.0) * pow((double)theta, 2.0) + 1.0);
        sim_rssi_array[i] = power * attenuation;		
    }
}

void update_sim()
{
	x = 0.71 * distance;
	distance = sqrt(pow(distance,2) + pow(x,2));
}


float sim_get_pow(float theta)
{
	int index = (adjust_angle_f(theta)) + 180;
	return sim_rssi_array[index];
}
