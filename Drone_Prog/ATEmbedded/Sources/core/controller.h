#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "com_AT.h"
#include "navdata.h"
#include "shared.h"

/******************************************************************************
********************** GLOBAL VARIABLES **************************************
*******************************************************************************/


#define POWER_MAX 120 //A calculer


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
int time_command(float distance);

/**
 * measure_distance: calcule la distance du drone a l'antenne apres avoir avancé a 45°
 * @arg: float power: puissance du signal
 * @return: float: la distance du drone a la victime
**/
float distance_measure(float ex_distance);

#endif // CONTROLLER_H
