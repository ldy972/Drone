#include "navdata.h"

/*******************************************************************************
 * GLOBAL VARIABLES
 * ****************************************************************************/

pthread_cond_t navdata_initialised = PTHREAD_COND_INITIALIZER;
navdata_t * navdata_struct = NULL;


int init_navdata_reception()
{
    int result = 0;
    result = initialize_navdata_socket();

    send_navdata("\x01\x00");

    result = receive_nav_data();

    if (result != 0) {
        if (navdata_struct->navdata_header.state == ARDRONE_NAVDATA_BOOTSTRAP) {
            printf("plop\n");
        }
    }

    return result;
}


int receive_nav_data()
{
    int result = 0;

    if (navdata_struct == NULL) {
        navdata_struct = malloc(sizeof(navdata_t));
    }

    int tab_navdata[1024];
    memset(tab_navdata, '\0', sizeof(tab_navdata)); 

    result = recieve_navdata(tab_navdata);
    printf("Recieved %d bytes\n", result);
    
    memcpy(navdata_struct, tab_navdata, sizeof(navdata_t));

    int i;
//    const unsigned char * const px = (unsigned char*)&navdata;

    printf("Head : %X\n", navdata_struct->navdata_header.seq);

    printf("Dump navdata_t :\n");
    for (i = 0; i < result/sizeof(int); i++) {
        printf("%X ", tab_navdata[i]);
        if (((i+1) % 12) == 0)
            printf("\n"); 
    }
    printf("\nDump navdata_t OK\n");

    // If everything went fine, navdata is OK

    return result;
}


int close_connection()
{
    return close_navdata_socket();
}

/*int duplicate(nav_data_type* navdata){
    if(navdata==NULL)
        navdata=(nav_data_type*)malloc(sizeof(nav_data_type));
    navdata->is_ready=0 ;
    memcpy(navdata,nav_data, sizeof(nav_data_type));
    return 0 ;
}*/
