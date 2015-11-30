#include "navdata.h"

/*******************************************************************************
 * GLOBALES VARIABLES
 * *****************************************************************************/
nav_data_type* nav_data ;


int init_connection()
{
    return initialize_navdata_socket();
}


int receive_nav_data()
{
    int result = 0;
    navdata_t full_navdata;

    printf("starting nav_data update\n");
    result = recieve_navdata(&full_navdata);
    
    printf("nav_data update\n");
    // If everything went fine, navdata is OK
    if (result == 0) {
        if(nav_data==NULL)
            nav_data=(nav_data_type*)malloc(sizeof(nav_data_type));

        memcpy(&(nav_data->nav_data), &(full_navdata.navdata_option), sizeof(navdata_demo_t));
        nav_data->is_ready = 1 ;
    }

    return result;
}


int close_connection()
{
    return close_navdata_socket();
}

int duplicate(nav_data_type* navdata){
    if(navdata==NULL)
        navdata=(nav_data_type*)malloc(sizeof(nav_data_type));
    navdata->is_ready=0 ;
    memcpy(navdata,nav_data, sizeof(nav_data_type));
    return 0 ;
}
