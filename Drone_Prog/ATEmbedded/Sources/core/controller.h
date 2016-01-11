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


#endif // CONTROLLER_H
