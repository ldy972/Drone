#include "controller.h"

int trajectory(){
	int end = 0;//On a atteint la cible 
	int power; //power measure
	init_simu(0); // Cap 0 
	//Full rotation 
	//Every 10 degrees : calculate the signal power and the cap
	int i;
	
	//while (1) {
		trajectory_measure.power = sim_get_power();
		trajectory_measure.cap = sim_get_heading();

		for (i=1; i<36; i++){
			printf("Cap:%f\n", get_heading());
			if (sim_get_power() >= trajectory_measure.power){
				trajectory_measure.power = sim_get_power();
				trajectory_measure.cap = sim_get_heading();
			}
			rotate_right(75,10.0);
		} //end for

		//On a le cap : aller vers ce cap tout en vérifiant que la puissance reçue augmente bien
	
		while ((sim_get_heading()-trajectory_measure.cap)<0.01){
			rotate_right(75,10.0);
			printf("Cap:%f\n", get_heading());
		}


	/*	power = trajectory_measure.power;
	
		while ((sim_get_power_move()>=power) && (sim_get_power_move < POWER_MAX)){
			power = sim_get_power_move();
			move_forward(75, trajectory_measure.cap); // TODO
			if (sim_get_power_move>=POWER_MAX) exit(0); // On est assez proche
		}
*/
		close_simu();

		//Algo en escargot
	//}
}


