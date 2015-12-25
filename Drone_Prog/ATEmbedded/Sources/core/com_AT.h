
#ifdef __cplusplus
extern "C" {
#endif

#ifndef COM_H
#define COM_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shared.h"
#include "udp_sender.h"

 /***********************************************************************
 * global defines and macro
 * *********************************************************************/
#define NB_ESSAI_UDP 1
#define DELAY(x) {usleep(x);}
#define POWER_P_SIZE 10	 
#define TAILLE_COMMANDE 258
#define NAVDATA_INIT_MSG "\x01\x00"

/***********************************************************************
 * global variables
 * *********************************************************************/
char maxSeqReach;
int16_t connectionOpen;
 
/***********************************************************************
 * Navdata configuration strings
 * *********************************************************************/
#define NAVDATA_DEMO_PARAM "general:navdata_demo"
#define NAVDATA_DEMO_VALUE "TRUE"
#define NAVDATA_MAGNETO_PARAM "general:navdata_option"

/***********************************************************************
 * HEADER AT defines
 * *********************************************************************/
#define H_AT_REF "AT*REF="
#define H_AT_PCMD "AT*PCMD="
#define H_AT_PCMD_MAG "AT*PCMD_MAG="
#define H_AT_FTRIM "AT*FTRIM="
#define H_AT_CONFIG "AT*CONFIG="
#define H_AT_CONFIG_IDS "AT*CONFIG_IDS="
#define H_AT_COMWDG "AT*COMWDG="
#define H_AT_CALIB "AT*CALIB="
#define H_AT_ACK "AT*CTRL="

/*static char H_AT_REF[] = "AT*REF=";
static char H_AT_PCMD[] = "AT*PCMD=";
static char H_AT_PCMD_MAG[] = "AT*PCMD_MAG=";
static char H_AT_FTRIM[] = "AT*FTRIM=";
static char H_AT_CONFIG[] = "AT*CONFIG=";
static char H_AT_CONFIG_IDS[] = "AT*CONFIG_IDS=";
static char H_AT_COMWDG[] = "AT*COMWDG=";
static char H_AT_CALIB[] = "AT*CALIB=";
static char H_AT_ACK[] = "AT*CTRL=";
*/
//static char REF_TAKE_OFF[] = "290718208";

/***********************************************************************
 * Internal types
 * *********************************************************************/

// Power Percentage
typedef enum power_percentage_{
    POS_POWER_5 = 1028443341,
    POS_POWER_10 = 1036831949,
    POS_POWER_20 = 1045220557,
    POS_POWER_25 = 1048576000,
    POS_POWER_50 = 1056964608,
    POS_POWER_75 = 1061158912,
    POS_POWER_100 = 1065353216,
    NEG_POWER_5 = -1119040307,
    NEG_POWER_10 = -1110651699,
    NEG_POWER_20 = -1102263091,
    NEG_POWER_25 = -1098907648,
    NEG_POWER_50 = -1090519040,
    NEG_POWER_75 = -1086324736,
    NEG_POWER_100 = -1082130432,
    NULL_POWER_VALUE = 0
} power_percentage ;

// AT*REF commands
typedef enum {
    REF_TAKE_OFF,
    REF_LAND,
    REF_EMERGENCY_STOP,
    REF_NO_EMERGENCY
} AT_REF_cmd;
    

/***********************************************************************
 * prototypes definitions
 * *********************************************************************/

// Taking off, landing and emregency mode
int take_off(void);
int land(void);
int emergency_stop(void);
int no_emergency_stop(void);

// Watchdog
int reload_watchdog(void);

// Intermediary functions
int move_forward(power_percentage power);
int move_rotate(power_percentage power);
int move_translate(power_percentage power);
int move_up_down(power_percentage power);

// Classic controls
int rotate_right(int power, int time);
int rotate_left(int power, int time);
int translate_right(int power, int time);
int translate_left(int power, int time); 
int forward(int power, int time);
int backward(int power, int time);
int up(int power, int time);
int down(int power, int time);

// Controls with magnetometer
int rotate_right_mag(int power, int time, float heading);
int rotate_left_mag(int power, int time, float heading);
int translate_right_mag(int power, int time, float heading);
int translate_left_mag(int power, int time, float heading); 
int forward_mag(int power, int time, float heading);
int backward_mag(int power, int time, float heading);

// Messages used for initialization
int configure_navdata_demo();
int configure_navdata_magneto();
int send_ack_message();
int trim_sensors();
int calibrate_magnetometer();

int initialize_connection_with_drone(void);

#endif // COM_H

#ifdef __cplusplus
}
#endif
