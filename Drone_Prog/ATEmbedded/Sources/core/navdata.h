#ifdef __cplusplus
extern "C" {
#endif

#ifndef NAVDATA_H
#define NAVDATA_H

#include <stdio.h>
#include <stdlib.h>

#include "shared.h"
#include "com_AT.h"
#include "navdata_structs.h"
#include "udp_sender.h"


/**
 * init_connection : Initialises the navadata socket to recieve packets
 * @arg : void
 * @return : 0 upon success
 */
int init_navdata_reception();

/**
 * receive_nav_data : Retrives a UDP packet containing navdata
 * @arg : nav_data_type : The structure to fill
 * @return : 0 upon success
 */
int update_navdata();

/**
 * close_connection : Closes the navadata socket
 * @arg : void
 * @return : 0 upon success
 */
int close_navdata_connection();

/**
 * get_altitude : Returns the current alitude of the drone in centimeters
 * @arg : void
 * @return : altitude field of the current navdata
 */
int32_t get_altitude();

/**
 * get_pitch : Returns the current pitch of the drone in degrees
 * @arg : void
 * @return : pitch field of the current navdata
 */
float32_t get_pitch();

/**
 * get_roll: Returns the current roll of the drone in degrees
 * @arg : void
 * @return : roll field of the current navdata
 */
float32_t get_roll();

/**
 * get_roll : Returns the current roll of the drone in degrees
 * @arg : void
 * @return : yaw field of the current navdata
 */
float32_t get_yaw();

float get_heading();

#endif //NAVDATA_H

#ifdef __cplusplus
}
#endif
