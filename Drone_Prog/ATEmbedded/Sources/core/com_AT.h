
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
 extern char maxSeqReach;
 extern int16_t connectionOpen;
 
/***********************************************************************
 * AT defines __USELESS __Examples for commande at max power
 * *********************************************************************/
#define NAVDATA_DEMO_CONFIG "\"general:navdata_demo\",\"TRUE\""

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
typedef enum power_percent{
    POS_POWER_5_ = 1028443341,
    POS_POWER_10_ = 1036831949,
    POS_POWER_20_ = 1045220557,
    POS_POWER_25_ = 1048576000,
    POS_POWER_50_ = 1056964608,
    POS_POWER_75_ = 1061158912,
    POS_POWER_100_ = 1065353216,
    NEG_POWER_5_ = -1119040307,
    NEG_POWER_10_ = -1110651699,
    NEG_POWER_20_ = -1102263091,
    NEG_POWER_25_ = -1098907648,
    NEG_POWER_50_ = -1090519040,
    NEG_POWER_75_ = -1086324736,
    NEG_POWER_100_ = -1082130432,
    NULL_POWER_VALUE = 0
} power_percent ;

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

int take_off(void);
int land(void);
int reload_watchdog(void);
int move_forward(power_percent power);
int move_rotate(power_percent power);
int move_translate(power_percent power);
int move_up_down(power_percent power);

int rotate_right(int power, int time);
int rotate_left(int power, int time);
int translate_right(int power, int time);
int translate_left(int power, int time); 
int forward(int power, int time);
int backward(int power, int time);
int up(int power, int time);
int down(int power, int time);


int emergency_stop(void);
int no_emergency_stop(void);

int configure_navdata();
int send_ack_message();
int trim_sensors();

int initialize_connection_with_drone(void);


#endif // COM_H

#ifdef __cplusplus
}
#endif
