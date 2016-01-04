#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "shared.h"
#include "navdata.h"
#include "com_AT.h"

int navdata_thread()
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

    return 0;
}


int watchdog_thread()
{
    while (1) {
        reload_watchdog();
        usleep(1500000);
    }
    return 0;
}


int main()
{
    int result = 1;
    pthread_t th_navdata;
    pthread_t th_watchdog;

    initialize_connection_with_drone();

    pthread_create(&th_navdata, NULL, navdata_thread, NULL);

    pthread_mutex_lock(&mutex_navdata_cond);
    pthread_cond_wait(&navdata_initialised, &mutex_navdata_cond);
    pthread_mutex_unlock(&mutex_navdata_cond);

    pthread_create(&th_watchdog, NULL, watchdog_thread, NULL);

    printf("It's on\n");
    sleep(2);

 
	/*int i;
	for (i=0; i<100; i++){
		printf("Yaw : %d\n", (int)get_yaw());
		printf("Cap : %d\n", (int)get_heading());
		sleep(1);
	}*/
    float cap;
    take_off();
    printf("First Altitude : %d\n", (int) get_altitude());
    sleep(2);

    calibrate_magnetometer();
    sleep(5);

    // Test for heading : turns a bit once a second for 5 seconds
    int i;
    for (i = 0; i < 50; i++) {
        printf("Altitude : %d\n", (int) get_altitude());
        printf("Cap : %f\n", get_heading());
        usleep(100000);

        if (i % 10 == 0) {
            rotate_right(50, 1);
        }
    }

    cap = get_heading();
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

    // Test for full rotation
    // BE CAREFUL : the drone derives quite easily
    //float32_t base_yaw = get_yaw();
    //rotate_right(75, 10);
    //while (abs((float) base_yaw - (float) get_yaw()) > 1.0) {
        //rotate_right(75,1);
    //}

    land();

    close_commands_socket();
    return 0;
}
