#ifndef DEF_SIM_DATA
#define DEF_SIM_DATA

#include "navdata.h"


#define step 10
static int data_range = 360/step;

void init_simu(float target); // initialise les tableaux de caps et de mesure. argument : cap cible
float sim_get_heading(void); // donne le cap actuel
int sim_get_power(void);// donne la puissance mesurée en direction du cap actuel
void close_simu(void); // libération mémoire



#endif
