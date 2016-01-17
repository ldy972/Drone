#ifndef DEF_SIM_REAL
#define DEF_SIM_REAL

#include "navdata.h"


#define step 10
static int data_range = 360/step;
extern float* sim_rssi_array;
	
void sim_rssi(float target);
void update_sim();
float sim_get_pow(float teta);



#endif
