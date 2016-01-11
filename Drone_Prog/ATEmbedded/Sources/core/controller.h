#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "com_AT.h"
#include "navdata.h"
#include "sim_data.h"

/******************************************************************************
********************** GLOBAL VARIABLES **************************************
*******************************************************************************/

struct measure{
	int power;
	int cap;
};

struct measure trajectory_measure ;

#define POWER_MAX 120; //A calculer


/**
 * trajectory : algorithm of the trajectory
 * @arg : void
 * @return : 0 upon success
**/

int trajectory();


#endif // CONTROLLER_H
