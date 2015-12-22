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
            printf("[NAV] Update\n");
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

    take_off();
    sleep(2);

    int i;
    for (i = 0; i < 100; i++) {
        printf("Altitude : %d\n", (int) get_altitude());
        usleep(100000);
    }

    land();

    close_commands_socket();
    return 0;
}
