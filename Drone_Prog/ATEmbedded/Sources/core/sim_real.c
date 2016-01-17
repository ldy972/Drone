
#include <stdlib.h>
#include <stdio.h>
#include "sim_real.h"
#include "navdata.h"
#include <math.h>

#define d_0 60.0


static float* sim_rssi_array=NULL;
static float d = d_0; // distance par rapport à la cible
static float x=0; // distance à parcourir à 45°
static float teta_max = 0; // cap de la plus grande puissance

void sim_rssi(float target){
	int i =0;
	int teta, orientation = 0;
	float a = 0;
	sim_rssi_array = malloc(sizeof(float)*360); // crée un tableau de 360 floats 
	p = -0.2255*d -14.527; // puissance reçue en face de la cible en fonction de la distance
	for (i=0; i<360; i++)
		{
			teta = i-180;
			orientation = (int)((float)teta - target)%360 ;
			a = (-3*pow(10,-5)*pow(orientation,2) + 1) // coeff d'atténuation de puissance en fonction de l'angle
			sim_rssi_array[i] = p*a;			
		}
	
}

void update_sim(){

	x = 0.71*d;
	d = sqrt(pow(d,2)+pow(x,2));
}


float sim_get_pow(float teta){
	int index = ((int)teta)%360 + 180;
	return sim_rssi_array[index];

}


