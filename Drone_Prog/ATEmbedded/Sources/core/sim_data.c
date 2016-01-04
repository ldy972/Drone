
#include <stdlib.h>
#include <stdio.h>
#include "sim_data.h"



/**
 * @overview : génère un tableau contenant data_range  valeur de cap, prises tous les step degrés
 * @arg :
 * @return : pointeur sur le tableau
 * */
float* sim_cap(void){
	int i =0;
	int data_range = 360/step;
	float* sim_cap_array=(float *) malloc(data_range * sizeof(float));

	for (i=0; i<data_range; i++)
		{
			sim_cap_array[i] = ((step*i)-180)/180;
		}
	return sim_cap_array;
}


/**
 * @overview : retourne la position du cap du tableau le plus proche du cap réel
 * @arg :
 * @return : heading
 * */
int sim_get_heading_pos(void){

	float* sim_cap_array=(float *) malloc(data_range * sizeof(float));
	sim_cap_array = sim_cap();

	float min = 1000.0;
	int i =0;
	float heading_pos,delta =0.0;

	for (i=0; i<data_range;i++)
		{

		 delta = get_heading()-sim_cap_array[i];
		 if (delta <0)
			{delta = -delta;}	
		 if (delta <min)
			{min = delta; heading_pos =i;}
		}
	return heading_pos;
}

float sim_get_heading(void){
	float* sim_cap_array =sim_cap();
	return sim_cap_array[sim_get_heading_pos()];
}
		


/**
 * @overview : génère un tableau contenant data_range (36) mesures de rssi normalisée (0 à 100), calculée en fonction de la valeur du cap cible (-1 à 1)
 * @arg :
 * @return : pointeur sur le tableau
 * */		
int* sim_rssi(float target){

	int max_rssi = 180;
	int min = 1000;
	int i,j = 0;
	float* sim_cap_array = sim_cap();
	int size_cap_array = (sizeof(sim_cap_array)/sizeof(float));

	int* sim_rssi_array=(int *) malloc(data_range * sizeof(int));
	int size_rssi_array =(sizeof(sim_rssi_array)/sizeof(int));
	float delta;
	
	//étape 1 : trouver le cap le plus proche de la cible parmis ceux engreistrés en simu
	
	for (i=0; i<size_cap_array;i++)
		{
			delta=(sim_cap_array[i]-target);
			if (delta < 0.0)
				{delta = -delta;}
			min = i;
		}

	//étape 2 normalisation des rssi : décroit symétriquement de part et d'autre du max
	sim_rssi_array[i] = max_rssi;
	for (j=i+1; j<size_rssi_array; j++)
		{
			sim_rssi_array[j] = max_rssi -(10*(j-i));
		}

	for (j=i-1; j>=0; j--)
		{
			sim_rssi_array[j] = max_rssi -(10*(j-i));
		}

	return sim_rssi_array;
	
}

int sim_get_power(void){
	int* sim_rssi_array = sim_rssi(get_heading());
	return sim_rssi_array[sim_get_heading_pos()];
}
	
int main (void)
{
return 1;
}
