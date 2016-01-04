#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "com_AT.h"
#include "navdata.h"


/******************************************************************************
********************** GLOBAL VARIABLES **************************************
*******************************************************************************/

struct trajectory_measure{
	int power;
	int cap;
};

int POWER_MAX 0; //A calculer


/**
 * trajectory : algorithm of the trajectory
 * @arg : void
 * @return : 0 upon success
**/

int trajectory();


#endif // CONTROLLER_H
