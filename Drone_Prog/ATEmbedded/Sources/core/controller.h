#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "com_AT.h"
#include "navdata.h"
#include "sim_data.h"

/******************************************************************************
********************** GLOBAL VARIABLES **************************************
*******************************************************************************/


#define POWER_MAX 120; //A calculer

typedef struct _trajectory_measure_t{
	int power;
	int cap;
} trajectory_measure_t;


/**
 * trajectory : algorithm of the trajectory
 * @arg : void
 * @return : 0 upon success
**/

int trajectory();


/**
 * time: calcul la nombre de commande move_forward a envoyer pour avancer de distance
 * @arg : float distance : la distance dont on veut avancer
 * @return : int: le nombre de commande a envoyer
**/
int time(float distance);

/**
 * measure_distance: calcule la distance du drone a l'antenne apres avoir avancé a 45°
 * @arg: float power: puissance du signal
 * @return: float: la distance du drone a la victime
**/
float measure_distance(float ex_distance);

#endif // CONTROLLER_H
