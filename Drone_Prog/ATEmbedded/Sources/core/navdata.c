#include "navdata.h"

/*******************************************************************************
 * GLOBAL VARIABLES
 * ****************************************************************************/

pthread_cond_t navdata_initialised = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex_navdata_cond = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_navdata_struct = PTHREAD_MUTEX_INITIALIZER;
navdata_t * navdata_struct = NULL;


int init_navdata_reception()
{
    int result = 0;
    int ok = 0;
    
    result = initialize_commands_socket();

    if ( result == 0) {
        result = initialize_navdata_socket();
        //printf("[NAV] Navdata socket ok\n");
    }

    if ( result == 0) {
        send_navdata("\x01\x00");
        //printf("[NAV] Navdata flag sent\n");
    }

    while (!ok) {
        result = update_navdata();

        if (result != 0) {
            if (navdata_struct->navdata_header.state & ARDRONE_NAVDATA_BOOTSTRAP) {
                ok = 1;
                //printf("[NAV] Bootstrap\n");
            }
        }
    }

    configure_navdata_demo();

    ok = 0;
    while (!ok) {
        result = update_navdata();

        if (result != 0) {
            if (navdata_struct->navdata_header.state & ARDRONE_COMMAND_MASK) {
                ok = 1;
                //printf("[NAV] Conf OK\n");
            }
        }
    }

    send_ack_message();

    ok = 0;
    while (!ok) {
        result = update_navdata();

        if (result != 0) {
            if (navdata_struct->navdata_header.state & ARDRONE_COMMAND_MASK) {
                ok = 1;
                //printf("[NAV] Ack\n");
            }
        }
    }

    configure_navdata_magneto();

    trim_sensors();

    pthread_mutex_lock(&mutex_navdata_cond);
    pthread_cond_signal(&navdata_initialised);
    pthread_mutex_unlock(&mutex_navdata_cond);

    return result;
}


int update_navdata()
{
    int result = 0;

    int tab_navdata[1024];
    memset(tab_navdata, '\0', sizeof(tab_navdata)); 

    result = recieve_navdata(tab_navdata);
    
    pthread_mutex_lock(&mutex_navdata_struct);
    if (navdata_struct == NULL) {
        navdata_struct = malloc(sizeof(navdata_t));
    }

    memcpy(navdata_struct, tab_navdata, sizeof(navdata_t));
    pthread_mutex_unlock(&mutex_navdata_struct);

    // If everything went fine, navdata is OK

    return result;
}


int close_navdata_connection()
{
    pthread_mutex_lock(&mutex_navdata_struct);
    free(navdata_struct);
    pthread_mutex_unlock(&mutex_navdata_struct);
    return close_navdata_socket();
}


int32_t get_altitude()
{
    int32_t altitude;

    pthread_mutex_lock(&mutex_navdata_struct);
    altitude = navdata_struct->navdata_option.altitude;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return altitude;
}

float32_t get_pitch()
{
    float32_t pitch;

    pthread_mutex_lock(&mutex_navdata_struct);
    pitch = navdata_struct->navdata_option.theta / 1000.0;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return pitch;
}

float32_t get_roll()
{
    float32_t roll;

    pthread_mutex_lock(&mutex_navdata_struct);
    roll = navdata_struct->navdata_option.phi / 1000.0;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return roll;
}

float32_t get_yaw()
{
    float32_t yaw;

    pthread_mutex_lock(&mutex_navdata_struct);
    yaw = navdata_struct->navdata_option.psi / 1000.0;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return yaw;
}

float get_heading()
{
    float heading;

    pthread_mutex_lock(&mutex_navdata_struct);
    heading = navdata_struct->navdata_magneto.heading_fusion_unwrapped;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return heading;
}
