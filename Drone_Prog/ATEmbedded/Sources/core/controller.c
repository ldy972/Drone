#include "controller.h"
#include "math.h"

/******************************************************************************
 * Global Variables                                                           *
 *****************************************************************************/

trajectory_measure_t trajectory_measure;

int trajectory(){
	int end = 0;//On a atteint la cible 
	int power; //power measure
	init_simu(0); // Cap 0 
	//Full rotation 
	//Every 10 degrees : calculate the signal power and the cap
	int i;
	float init_cap;

	//while (1) {
		trajectory_measure.power = sim_get_power();
		trajectory_measure.cap = sim_get_heading();
		init_cap = get_heading();

		rotate_right_mag(75,10.0);
		while(get_heading()<init_cap+360)
		{
			printf("Cap:%f\n", get_heading());
			printf("Power:%d\n", trajectory_measure.power);
			printf("Cap simu:%f\n", trajectory_measure.cap);

			if (sim_get_power() >= trajectory_measure.power){
				trajectory_measure.power = sim_get_power();
				trajectory_measure.cap = sim_get_heading();
			}
			rotate_right_mag(75,10.0);
	        } //end while
		sleep(5);
		init_cap = get_heading();

		rotate_left_mag(75,10.0);
		printf("\ncap:%f\n", get_heading());

		while(get_heading()>(init_cap-90)){
			rotate_left_mag(75,10.0);
			printf("\ncap:%f\n", get_heading());
		}
		sleep(5);

		init_cap=get_heading();
		forward_mag(75,10,init_cap);
		sleep(5);				
		//On a le cap : aller vers ce cap tout en vérifiant que la puissance reçue augmente bien
	
		/*while ((sim_get_heading()-trajectory_measure.cap)<0.01){
			rotate_right(75,10.0);
			printf("Cap:%f\n", get_heading());
		}
*/

	/*	power = trajectory_measure.power;
	
		while ((sim_get_power_move()>=power) && (sim_get_power_move < POWER_MAX)){
			power = sim_get_power_move();
			move_forward(75, trajectory_measure.cap); // TODO
			if (sim_get_power_move>=POWER_MAX) exit(0); // On est assez proche
		}
*/
		close_simu();

	return 0;		//Algo en escargot
	//}
}


