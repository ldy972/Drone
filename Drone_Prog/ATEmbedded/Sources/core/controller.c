#include "controller.h"

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



int main()
{
    int result = 1;
    pthread_t th_navdata;

    initialize_connection_with_drone();

    /*pthread_create(&th_navdata, NULL, navdata_thread, NULL);

    pthread_mutex_lock(&mutex_navdata_cond);
    pthread_cond_wait(&navdata_initialised, &mutex_navdata_cond);
    pthread_mutex_unlock(&mutex_navdata_cond);
*/
    result = init_navdata_reception();
    if (result != 0) {
        result = 1;
        printf("[NAV] Ready\n");
        // Navdata reception loop
            printf("[NAV] Update\n");
            result = update_navdata();
    }
    printf("It's on\n");
  //  sleep(5);

    int took_off = 0;
    while (!took_off) {
        take_off();
    /*    printf("[MAIN] Prise mutex\n");
        pthread_mutex_lock(&mutex_navdata_struct);
      */  printf("[MAIN] \t%13d:%s\n",  (int) navdata_struct->navdata_option.altitude,               "altitude");
        if (navdata_struct->navdata_option.altitude != 0) {
            printf("[MAIN] I believe\n");
            took_off = 1;
        }
        /*printf("[MAIN] Relachement mutex\n");
        pthread_mutex_unlock(&mutex_navdata_struct);
        sleep(1);*/

    if (result != 0) {
        printf("[NAV] Ready\n");
        // Navdata reception loop
            printf("[NAV] Update\n");
            result = update_navdata();
    }
    }
    sleep(5);

    land();

    /*int landed = 0;
    while (!landed) {
        land();
        pthread_mutex_lock(&mutex_navdata_struct);
        if (navdata_struct->navdata_option.altitude == 0) {
            printf("[MAIN] I can fly\n");
            landed = 1;
        }
        pthread_mutex_unlock(&mutex_navdata_struct);
    }*/

    close_commands_socket();
    return 0;
}
