#include "navdata.h"


int init_connection()
{
    return initialize_navdata_socket();
}


int receive_nav_data(nav_data_type * navdata)
{
    int result = 0;
    navdata_t full_navdata;

    navdata->is_ready = 0;
    result = recieve_navdata(&full_navdata);
    
    // If everything went fine, navdata is OK
    if (result == 0) {
        navdata->is_ready = 1;
        memcpy(&(navdata->nav_data), &(full_navdata.navdata_option), sizeof(navdata_demo_t));
    }

    return result;
}


int close_connection()
{
    return close_navdata_socket();
}
