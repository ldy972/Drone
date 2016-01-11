#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#include "shared.h"
#include "navdata.h"
#include "com_AT.h"
#include "controller.h"
#include "sim_data.h"

/*void Emergency_exit (int signum)
{

	land();
	close_commands_socket();
	exit(signum);
}
*/

/*void * simu_thread ()
{ 
	float target = 0.0;
	printf("Simulation data initializing");
	init_simu(target);
	while (1)
	{
		sim_update();
		printf("heading : %f\n pow : %d\n target : %f", sim_get_heading(), sim_get_power(), target);
		usleep(1000000);
	}
	return NULL;
}
*/


void * navdata_thread()
{
    int result = 1;
    printf("[NAV] Init\n");
    result = init_navdata_reception();
    printf("[NAV] Init OK\n");

    if (result != 0) {
        printf("[NAV] Ready\n");
        // Navdata reception loop
        while (result) {
            result = update_navdata();
        }
    }
    printf("F*ck this, I'm outta here\n");

    return NULL;
}


void * watchdog_thread()
{
    while (1) {
        reload_watchdog();
        usleep(1500000);
    }

    return NULL;
}


int main()
{
   // signal(SIGINT, Emergency_exit);
    //int result = 1;
    int i;
    pthread_t th_navdata;
    pthread_t th_watchdog;
//    pthread_t th_simu;

    initialize_connection_with_drone();

    pthread_create(&th_navdata, NULL, navdata_thread, NULL);

    pthread_mutex_lock(&mutex_navdata_cond);
    pthread_cond_wait(&navdata_initialised, &mutex_navdata_cond);
    pthread_mutex_unlock(&mutex_navdata_cond);

    pthread_create(&th_watchdog, NULL, watchdog_thread, NULL);

   // pthread_create(&th_simu, NULL,simu_thread, NULL);

    printf("It's on\n");
    sleep(2);

    take_off();

    //printf("First Altitude : %d\n", (int) get_altitude());
    //sleep(2);


    calibrate_magnetometer();

    sleep(7);

    // Indefinitely print magneto
    /*while (1) {
        print_navdata_magneto();
        usleep(500000);
    }*/

    //trajectory();

    // Test for heading : turns a bit once a second for 5 seconds
    //for (i = 0; i < 50; i++) {
        //printf("Altitude : %d\n", (int) get_altitude());
        //printf("Cap : %f\n", get_heading());
        //usleep(100000);

        //if (i % 10 == 0) {
            //rotate_right(50, 1);
        //}
    //}

    /*cap = get_heading();
    printf("\nCAP A ATTEINDRE SA MERE : %f\n", cap);
    sleep(2);
   
    //On revient à la position initiale
    for (i=0; i<50; i++){
	printf("Cap : %f\n", get_heading());
        usleep(100000);
        if (i%10 == 0){
		rotate_left(50,1);		
	}
    }
	
    sleep(3);

    //On revient vers le cap

    while((cap-get_heading())<0.01){
	rotate_right(50,1);
    }

    printf("\nCAP ATTEINT SA MERE : %f\n", get_heading());
    */

    // Test for full rotation
    // BE CAREFUL : the drone derives quite easily
    //float32_t base_yaw = get_yaw();
    //rotate_right(75, 10);
    //while (abs((float) base_yaw - (float) get_yaw()) > 1.0) {
        //rotate_right(75,1);
    //}


    // Test for altitude : goes up once every second for 5 seconds
    //for (i = 0; i < 50; i++) {
        //printf("Altitude : %d\n", (int) get_altitude());
        //printf("Cap : %f\n", get_heading());
        //usleep(100000);

        //if (i % 10 == 0) {
            //up(50, 1);
        //}
    //}


    //printf("Test Heading\n");

//    float heading = get_heading();

    //if (heading < -1.0)
      //  heading += 2.0;

    // Tests for heading : make the drone move relatively to a given heading
  /*  for (i = 0; i < 25; i++) {
        printf("Heading : %f\n", heading);
        translate_right_mag(10, 1, heading);
        heading -= 2.0;
        usleep(50000);
    }
*/

    //land();


    //printf("Test Rotation\n");


    /*float heading = get_heading() - 0.5;

    if (heading < -1.0)
        heading += 2.0;

    // Tests for heading : make the drone move relatively to a given heading
    for (i = 0; i < 10; i++) {
        printf("Heading : %f\n", heading);
        printf("Magneto rad : %f\n", get_magneto_radius());
        translate_right_mag(50, 1, heading);
    }
*/
 	trajectory();
   	land();

    // Tests for rotation 
/*        printf("first height : %f\n", get_altitude());
        up(100.0,280.0);
        sleep(2) ;
        printf("height en l'air : %f\n", get_altitude());    
        land();
*/

/*    printf("Test Rotation\n");

    // Tests for rotation 
        printf("first heading : %f\n", get_heading());
        rotate_right_mag(100.0,360.0);
        printf("final heading : %f\n", get_heading());    
        sleep(1);
        land();
*/


    close_commands_socket();
    return 0;
}
