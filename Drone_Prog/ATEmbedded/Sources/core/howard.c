#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#include "shared.h"
#include "navdata.h"
#include "com_AT.h"
#include "controller.h"
#include "sim_real.h"

void Emergency_exit (int signum)
{

	land();
	close_commands_socket();
	exit(signum);
}


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
}*/



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
#ifndef FULL_SIMU
    signal(SIGINT, Emergency_exit);

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
    sleep(2);
    calibrate_magnetometer();

    sleep(7);

    // Indefinitely print magneto
    /*while (1) {
        print_navdata_magneto();
        usleep(500000);
    }*/

    /*************************
     * Normal behaviour      *
     *************************/
    //trajectory();

    /*************************
     * Tests                 *
     *************************/
    /*sleep(2) ;

    printf("orientation\n") ;
    printf("first heading : %f\n", get_heading()) ;
    forward(10, 2.0);
    //forward_mag(100, 150, get_heading());
    sleep(2) ;

    //orientate_mag(100, get_heading() + 10.0);*/

    sleep(2) ;
    land();
    close_commands_socket();

#else
    initialize_simulation();
    trajectory();
    finish_simulation();
#endif

    return 0;
}
