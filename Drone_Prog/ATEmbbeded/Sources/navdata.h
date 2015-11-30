#ifdef __cplusplus
extern "C" {
#endif

#ifndef NAVDATA_H
#define NAVDATA_H

#include <stdio.h>
#include <stdlib.h>
#include "navdata_structs.h"
#include "udp_sender.h"



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
int receive_nav_data();

/**
 * close_connection : Closes the navadata socket
 * @arg : void
 * @return : 0 upon success
 */
int close_connection();

/**
 * @brief duplicate
 * @param navdata
 * @return
 */
int duplicate(nav_data_type* navdata);
#endif //NAVDATA_H
#ifdef __cplusplus
}
#endif
