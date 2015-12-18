#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>

#include "navdata_structs.h"
#include "debug.h"

/******************************************************************************
 * AT_Commands related
 *****************************************************************************/
extern pthread_mutex_t mutex_seq_num;
 

/******************************************************************************
 * Navdata related
 *****************************************************************************/

// Condition signaling that navdata communication is up and running
extern pthread_cond_t navdata_initialised;
extern pthread_mutex_t mutex_navdata_cond;

// Storage for navdata
extern pthread_mutex_t mutex_navdata_struct;
extern navdata_t * navdata_struct;


#endif
