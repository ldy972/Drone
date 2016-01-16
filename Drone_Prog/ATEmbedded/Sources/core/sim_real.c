
#include <stdlib.h>
#include <stdio.h>
#include "sim_data.h"
#include "navdata.h"
#include <math.h>

#define d_0 60.0

static float* sim_cap_array=NULL;
static float* sim_rssi_array=NULL;
static float d = d_0; // distance par rapport à la cible
static float x=0; // distance à parcourir à 45°
static float teta_max = 0; // cap de la plus grande puissance

// LOCAL

/**
 * @overview : génère un tableau contenant data_range  valeur de cap, prises tous les step degrés
 * @arg :
 * @return : pointeur sur le tableau
 * */
void sim_cap(void){
	int i =0;
	//int data_range = 360/step;
	sim_cap_array=(float *) malloc(data_range * sizeof(float));
	
	

	for (i=0; i<data_range; i++)
		{
			sim_cap_array[i] = ((step*i)-180)/180;
		}
	
}


/**
 * @overview : retourne la position du cap du tableau le plus proche du cap réel
 * @arg :
 * @return : heading
 * */
int sim_get_heading_pos(void){


	float min = 1000.0;
	int i =0;
	float heading_pos,delta =0.0;

	for (i=0; i<data_range;i++)
		{

		 delta = get_heading()-sim_cap_array[i];
		 if (fabs(delta) <min)
			{min = delta; heading_pos =i;}
		}
	return heading_pos;
}

/**
 * @overview : génère 36 mesures de P normalisée (entre 0 et 1) en fonction de Teta (orientation par rapport au cap ciblé). Distance initiale à la cible : d_0 =60metres
 * @arg : le cap ciblé
 * @return : le cap avec la plus grande puissance
 * */		
void sim_rssi(float target){
	
	sim_rssi_array=(int *) malloc(data_range * sizeof(float));
	float p = (-0.2255*d - 14.527);
	float teta = 0;// cap actuel du drone
	float a =0.0; // coeff d'attenuation en fonction de teta
	float max = -5.0;
	
	
	// pour différents caps du drone (de -180 à +180), on calcule la puissance reçue en fonction du cap de la cible (target)
	for (teta=-180; teta<=180;teta+=10)
		{
			a = (-3*pow(10,-5)*pow(fabs(target-teta),2) + 1));
			sim_rssi_array[i] = a*p;
			if (sim_rssi_array[i] > max)
				{teta_max = teta;}
			
		}
	// on met à jours la distance à parcourir à 45° (x) et la distance à laquelle on sera de la cible après ce déplacement (d)
	x = 0.71*d;
	d= sqrt(pow(d,2)+pow(x,2));
	
	
}


			
		
	
	
	

int sim_get_target_pos (void){
	int i, target_pos = 0;
	int size_rssi_array =(sizeof(sim_rssi_array)/sizeof(float));
	
		
	for(i=0; i<size_rssi_array; i++)
		{
			if (sim_rssi_array[i] >= 0.9)
				{target_pos =i;}
		}
	return target_pos;
}

// GLOBAL




/**
 * @overview : donne la distance x à parcourir à 45° de la cible;
 * @arg :
 * @return : 
 * */	
float get_x(){
	return x;
}


/**
 * @overview : donne le cap avec la plus grande puissance (i.e cap face auquel on veut s'orienter avant de pivoter à 45°)
 * @arg :
 * @return : 
 * */	
float get_teta_max(){
	return teta_max;
}

/**
 * @overview : initialise la simu : la cible est à 60m au Nord.
 * @arg :
 * @return : 
 * */	
void init_simu(){
	sim_rssi(0.0);
}

/**
 * @overview : met à jour les données
 * @arg :
 * @return : 
 * */	
void sim_update(){
	sim_rssi(get_teta_max());
}
	


void close_simu(void){
	free (sim_cap_array);
	sim_cap_array = NULL;
	free (sim_rssi_array);
	sim_rssi_array = NULL;
}
	
