#include "navdata.h"

/*******************************************************************************
 * GLOBAL VARIABLES
 * ****************************************************************************/

pthread_cond_t navdata_initialised = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex_navdata_cond = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_navdata_struct = PTHREAD_MUTEX_INITIALIZER;
navdata_t * navdata_struct = NULL;

/*******************************************************************************
 * Local Functions prototypes
 * ****************************************************************************/

void decode_navdata(unsigned char * data, int size);


/*******************************************************************************
 * Functions declarations
 * ****************************************************************************/

int init_navdata_reception()
{
    int result = 0;
    int ok = 0;
    int navdata_configured = 0;

    result = initialize_commands_socket();

    if (result == 0) {
        //printf("[NAV] Commands socket ok\n");
        result = initialize_navdata_socket();
    }

    if (result == 0) {
        //printf("[NAV] Navdata socket ok\n");
        result = send_navdata("\x01\x00");
    }

    if (result == 0) {
        //printf("[NAV] Navdata flag sent\n");
        //while (!ok) {
            result = update_navdata();

            if (result != 0) {
                if (navdata_struct->navdata_header.state & ARDRONE_NAVDATA_BOOTSTRAP) {
                    ok = 1;
                    //printf("[NAV] Bootstrap\n");
                } else {
                    navdata_configured = 1;
                }
            }
        //}
    }

    if (!navdata_configured) {

        result = configure_navdata_demo();

        if (result == 0) {
            //printf("[NAV] Navdata conf sent\n");
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
    }

    trim_sensors();

    printf("[NAV] Ready. Battery level : %d\n", get_battery_level());

    pthread_mutex_lock(&mutex_navdata_cond);
    pthread_cond_signal(&navdata_initialised);
    pthread_mutex_unlock(&mutex_navdata_cond);

    return result;
}


int update_navdata()
{
    int result = 0;

    uint8_t tab_navdata[1024];
    memset(tab_navdata, '\0', sizeof(tab_navdata)); 

    result = recieve_navdata(tab_navdata);

    decode_navdata(tab_navdata, result);

    // If everything went fine, navdata is OK

    return result;
}

// Decode the recieved navdata and store it in 
void decode_navdata(unsigned char * data, int size)
{
    pthread_mutex_lock(&mutex_navdata_struct);

    // Allocate the navdata structure if it is nt already done
    if (navdata_struct == NULL) {
        navdata_struct = malloc(sizeof(navdata_t));
    }

    memcpy(&(navdata_struct->navdata_header), data, sizeof(navdata_header_t));

    // Run through the data to fill the structure accordingly
    int i;
    int demo_ok = 0;
    int mag_ok = 0;
    for (i = sizeof(navdata_header_t); i < size; i++) {
        navdata_option_header_t option_header;
        memcpy(&option_header, data + i, sizeof(navdata_option_header_t));

        if (!demo_ok && option_header.tag == option_demo) {
            memcpy(&(navdata_struct->navdata_demo), data + i, sizeof(navdata_demo_t));
            i += option_header.size;
            demo_ok = 1;
        } else if (!mag_ok && option_header.tag == option_magneto) {
            navdata_struct->navdata_magneto.header = * (navdata_option_header_t *) (data + i);
            i += sizeof(navdata_option_header_t);
            navdata_struct->navdata_magneto.mx = * (uint16_t *) (data + i);
            i += sizeof(uint16_t);
            navdata_struct->navdata_magneto.my = * (uint16_t *) (data + i);
            i += sizeof(uint16_t);
            navdata_struct->navdata_magneto.mz = * (uint16_t *) (data + i);
            i += sizeof(uint16_t);
            navdata_struct->navdata_magneto.magneto_raw = * (vector31_t *) (data + i);
            i += sizeof(vector31_t);
            navdata_struct->navdata_magneto.magneto_rectified = * (vector31_t *) (data + i);
            i += sizeof(vector31_t);
            navdata_struct->navdata_magneto.magneto_offset = * (vector31_t *) (data + i);
            i += sizeof(vector31_t);
            navdata_struct->navdata_magneto.heading_unwrapped = * (float *) (data + i);
            i += sizeof(float);
            navdata_struct->navdata_magneto.heading_gyro_unwrapped = * (float *) (data + i);
            i += sizeof(float);
            navdata_struct->navdata_magneto.heading_fusion_unwrapped = * (float *) (data + i);
            i += sizeof(float);
            navdata_struct->navdata_magneto.magneto_calibration_ok = * (char *) (data + i);
            i += sizeof(char);
            navdata_struct->navdata_magneto.magneto_state = * (uint32_t *) (data + i);
            i += sizeof(uint32_t);
            navdata_struct->navdata_magneto.magneto_radius = * (float *) (data + i);
            i += sizeof(float);
            navdata_struct->navdata_magneto.error_mean = * (float *) (data + i);
            i += sizeof(float);
            navdata_struct->navdata_magneto.error_var = * (float *) (data + i);
            i += sizeof(float);
            mag_ok = 1;
        }
    }

    pthread_mutex_unlock(&mutex_navdata_struct);
}


int close_navdata_connection()
{
    pthread_mutex_lock(&mutex_navdata_struct);
    free(navdata_struct);
    pthread_mutex_unlock(&mutex_navdata_struct);
    return close_navdata_socket();
}


uint32_t get_battery_level()
{
    uint32_t battery_level;

    pthread_mutex_lock(&mutex_navdata_struct);
    battery_level = navdata_struct->navdata_demo.vbat_flying_percentage;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return battery_level;
}

int32_t get_altitude()
{
    int32_t altitude;

    pthread_mutex_lock(&mutex_navdata_struct);
    altitude = navdata_struct->navdata_demo.altitude;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return altitude;
}

float32_t get_pitch()
{
    float32_t pitch;

    pthread_mutex_lock(&mutex_navdata_struct);
    pitch = navdata_struct->navdata_demo.theta / 1000.0;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return pitch;
}

float32_t get_roll()
{
    float32_t roll;

    pthread_mutex_lock(&mutex_navdata_struct);
    roll = navdata_struct->navdata_demo.phi / 1000.0;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return roll;
}

float32_t get_yaw()
{
    float32_t yaw;

    pthread_mutex_lock(&mutex_navdata_struct);
    yaw = navdata_struct->navdata_demo.psi / 1000.0;
    pthread_mutex_unlock(&mutex_navdata_struct);
    
    if(yaw < 0.0)
    {
       return yaw + 360.0 ;
    } 
    else
    {
        return yaw;
    }
   
}

float get_vx()
{
    float vx;

    pthread_mutex_lock(&mutex_navdata_struct);
    vx = navdata_struct->navdata_demo.vx;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return vx;
}

float get_vy()
{
    float vy;

    pthread_mutex_lock(&mutex_navdata_struct);
    vy = navdata_struct->navdata_demo.vy;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return vy;
}

float get_vz()
{
    float vz;

    pthread_mutex_lock(&mutex_navdata_struct);
    vz = navdata_struct->navdata_demo.vx;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return vz;
}

float get_heading()
{
    float heading;

    pthread_mutex_lock(&mutex_navdata_struct);
    heading = navdata_struct->navdata_magneto.heading_fusion_unwrapped;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return heading;
}

float get_magneto_radius()
{
    float radius;

    pthread_mutex_lock(&mutex_navdata_struct);
    radius = navdata_struct->navdata_magneto.magneto_radius;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return radius;
}

float get_heading_unwrapped()
{
    float heading_un;

    pthread_mutex_lock(&mutex_navdata_struct);
    heading_un = navdata_struct->navdata_magneto.heading_unwrapped;
    pthread_mutex_unlock(&mutex_navdata_struct);

    return heading_un;
}

void print_navdata_magneto()
{
    pthread_mutex_lock(&mutex_navdata_struct);
    printf("Navdata magneto\n");
    printf("Mx : %d => %x\n", navdata_struct->navdata_magneto.mx, *(uint16_t*) &navdata_struct->navdata_magneto.mx);
    printf("My : %d => %x\n", navdata_struct->navdata_magneto.my, *(uint16_t *) &navdata_struct->navdata_magneto.my);
    printf("Mz : %d => %x\n", navdata_struct->navdata_magneto.mz, *(uint16_t *) &navdata_struct->navdata_magneto.mz);
    printf("Magneto raw : [%f, %f, %f] => [%x, %x, %x]\n", navdata_struct->navdata_magneto.magneto_raw.x, navdata_struct->navdata_magneto.magneto_raw.y, navdata_struct->navdata_magneto.magneto_raw.z, *(uint32_t *) &navdata_struct->navdata_magneto.magneto_raw.x, *(uint32_t *) &navdata_struct->navdata_magneto.magneto_raw.y, *(uint32_t *) &navdata_struct->navdata_magneto.magneto_raw.z);
    printf("Magneto rectified : [%f, %f, %f] => [%x, %x, %x]\n", navdata_struct->navdata_magneto.magneto_rectified.x, navdata_struct->navdata_magneto.magneto_rectified.y, navdata_struct->navdata_magneto.magneto_rectified.z, *(uint32_t *) &navdata_struct->navdata_magneto.magneto_rectified.x, *(uint32_t *) &navdata_struct->navdata_magneto.magneto_rectified.y, *(uint32_t *) &navdata_struct->navdata_magneto.magneto_rectified.z);
    printf("Magneto offset : [%f, %f, %f] => [%x, %x, %x]\n", navdata_struct->navdata_magneto.magneto_offset.x, navdata_struct->navdata_magneto.magneto_offset.y, navdata_struct->navdata_magneto.magneto_offset.z, *(uint32_t *) &navdata_struct->navdata_magneto.magneto_offset.x, *(uint32_t *) &navdata_struct->navdata_magneto.magneto_offset.y, *(uint32_t *) &navdata_struct->navdata_magneto.magneto_offset.z);
    printf("Heading unwrapped : %f => %x\n", navdata_struct->navdata_magneto.heading_unwrapped, *(uint32_t *) &navdata_struct->navdata_magneto.heading_unwrapped);
    printf("Heading gyro unwrapped : %f => %x\n", navdata_struct->navdata_magneto.heading_gyro_unwrapped, *(uint32_t *) &navdata_struct->navdata_magneto.heading_gyro_unwrapped);
    printf("Heading fusion unwrapped : %f => %x\n", navdata_struct->navdata_magneto.heading_fusion_unwrapped, *(uint32_t *) &navdata_struct->navdata_magneto.heading_fusion_unwrapped);
    printf("Calib OK : %c => %x\n", navdata_struct->navdata_magneto.magneto_calibration_ok, *(uint8_t *) &navdata_struct->navdata_magneto.magneto_calibration_ok);
    printf("Magneto state: %i => %x\n", navdata_struct->navdata_magneto.magneto_state, *(uint32_t *) &navdata_struct->navdata_magneto.magneto_state);
    printf("Magneto radius: %f => %x\n", navdata_struct->navdata_magneto.magneto_radius, *(uint32_t *) &navdata_struct->navdata_magneto.magneto_radius);
    printf("Error mean: %f => %x\n", navdata_struct->navdata_magneto.error_mean, *(uint32_t *) &navdata_struct->navdata_magneto.error_mean);
    printf("Error var: %f => %x\n", navdata_struct->navdata_magneto.error_var, *(uint32_t *) &navdata_struct->navdata_magneto.error_var);
    
    // dump navdata
    unsigned int i;
    const unsigned char * const px = (unsigned char*)navdata_struct;

    for (i = 0; i < sizeof(navdata_t); ++i) {
        printf("%02X", px[i]);
        if ((i+1) % 2 == 0) {
            printf(" ");
        }
        if ((i+1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    pthread_mutex_unlock(&mutex_navdata_struct);
}
