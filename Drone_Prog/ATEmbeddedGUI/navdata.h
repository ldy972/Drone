#ifdef __cplusplus
extern "C" {
#endif

#ifndef NAVDATA_H
#define NAVDATA_H

#include "navdata_structs.h"
#include "udp_sender.h"

// Structure containing navdata and a flag indicating if it is ready to be copied
typedef struct nav_data_type{
    navdata_demo_t nav_data;
    int is_ready ;
}nav_data_type;


nav_data_type nav_data;


/**
 * init_connection : Initialises the navadata socket to recieve packets
 * @arg : void
 * @return : 0 upon success
 */
int init_connection();

/**
 * receive_nav_data : Retrives a UDP packet containing navdata
 * @arg : nav_data_type : The structure to fill
 * @return : 0 upon success
 */
int receive_nav_data(nav_data_type * navdata);

/**
 * close_connection : Closes the navadata socket
 * @arg : void
 * @return : 0 upon success
 */
int close_connection();


#endif //NAVDATA_H
#ifdef __cplusplus
}
#endif
