#include "navdata.h"

/*******************************************************************************
 * GLOBAL VARIABLES
 * *****************************************************************************/

navdata_t * navdata = NULL;


int init_connection()
{
    return initialize_navdata_socket();
}


int receive_nav_data()
{
    int result = 0;

    if (navdata == NULL) {
        navdata = malloc(sizeof(navdata_t));
    }

    navdata_t full_navdata;

    result = recieve_navdata(navdata);
    
    unsigned int i;
    const unsigned char * const px = (unsigned char*)&navdata;

    printf("Dump navdata_t :\n");
    for (i = 0; i < sizeof(navdata_t); i++) {
        printf("%02X", px[i]);
        if (((i+1) % 2) == 0)
            printf(" ");
        if (((i+1) % 12) == 0)
            printf("\n"); 
    }
    printf("\nDump navdata_t OK\n");

    /*/ If everything went fine, navdata is OK
    if (result == 0) {
        if ( == NULL) {
            fprintf(stderr, "Navdata copy error");
            return 1;
        }
        nav_data->is_ready = 1 ;
    }*/

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
