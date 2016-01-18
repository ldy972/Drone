#include "controller.h"
#include "math.h"

/******************************************************************************
 * Global Variables                                                           *
 *****************************************************************************/

int time_command(float distance){
	if (distance<=0.0) return 0;
	else if (distance<=0.5) return 10;
	else if (distance<=1.5) return 20;
	else if (distance<=2.5) return 30;
	else if (distance<=3.5) return 40;
	else if (distance<=5.0) return 50;
	else if (distance<=6.0) return 60;
	else if (distance<=8.0) return 70;
	else if (distance<=10.0) return 80;
	else if (distance<=12.0) return 90;
	else if (distance <= 14.0) return 100;
	else if (distance <= 16.0) return 110;
	else return 120;
}


float distance_measure(float ex_a_parcourir){
	return ex_a_parcourir;
}


trajectory_measure_t trajectory_measure;

int trajectory(){
	int indice = 0;
	float distance; //distance measure
	float distance_todo; //distance to cross
	float ex_distance=20.0;
	float init_cap; //initial heading
	float power;

	while (indice<10) { 

		indice ++;

		//Full rotation
		//Every 10 degrees: calculate the signal power and the cap
		trajectory_measure.power = sim_get_power();
		trajectory_measure.cap = sim_get_heading();
		init_cap = get_heading();

		rotate_right_mag(75,10.0);
		printf("Rotation 360\n");
		while(get_heading()<init_cap+360)
		{
			printf("Cap:%f\n", get_heading());
			printf("Power:%f\n", trajectory_measure.power);
			printf("Cap simu:%f\n", trajectory_measure.cap);

			if (sim_get_power() >= trajectory_measure.power){
				trajectory_measure.power = sim_get_power();
				trajectory_measure.cap = sim_get_heading();
			}
			rotate_right_mag(75,10.0);
	        } //end while
		sleep(5);
		
		//We have the right direction and the power related to it
		if (trajectory_measure.power >= POWER_MAX) return 0; //We are close enough

		//Rotation toward the right direction
		while((get_heading()-trajectory_measure.cap)>5.0){
			rotate_right_mag(75,5.0);
		}

		printf("\ncap:%f\n", get_heading());
		init_cap = get_heading();

		sleep(1);

		//Measurement of the distance from the phone and the distance to cross at 45° from the right head
		distance = distance_measure(ex_distance);
		distance_todo = distance * 0.71; //cosinus(45)

		//Rotation of 45° from the cap
		rotate_right_mag(75,45.0);
		sleep(3);

		//Moving forward and checking the power is increasing
		int i = time_command(distance_todo);
		/*power = sim_get_power();
		move_forward_mag(75,1,init_cap);
		i--;

		while ((sim_get_power_move()>=power) && (i>0)){
			move_foward_mag(75, 1, init_cap);
			i--;
			power = sim_get_power();
		}
		*/
		move_forward_mag(75,i,init_cap);
		ex_distance = distance_todo;
	}

	return 0;
}


