#include "controller.h"

int trajectory(){
	int end = 0;//On a atteint la cible 
	int power; //power measure

	//Full rotation 
	//Every 10 degrees : calculate the signal power and the cap
	int i;
	
	while (1) {
		trajectory_measure.power = get_signal_power();
		trajectory_measure.cap = get_heading();

		for (i=1; i<36; i++){
			if (get_signal_power() >= trajectory_measure.power){
				trajectory_measure.power = get_signal_power();
				trajectory_measure.cap = get_heading();
			}
			rotate_right(75,10); //rotate_right(power, degres) TODO
		} //end for

		//On a le cap : aller vers ce cap tout en vérifiant que la puissance reçue augmente bien
	
		while ((get_heading()-trajectory_measure.cap)<0.01){
			rotate_right(75,10);
		}

		power = trajectory_measure.power;
	
		while ((get_signal_power()>=power) && (get_signal_power < POWER_MAX)){
			power = get_signal_power();
			move_forward(75, trajectory_measure.cap); // TODO
			if (get_signal_power>=POWER_MAX) exit(0); // On est assez proche
		}


		//Algo en escargot

	}
}


