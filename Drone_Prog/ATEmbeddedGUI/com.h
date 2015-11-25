
#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "udp_sender.h"
#include "debug.h"

 /***********************************************************************
 * global defines and macro
 * *********************************************************************/
#define NB_ESSAI_UDP 10
#define DELAY(x) {usleep(x);}
#define POWER_P_SIZE 10	 


/***********************************************************************
 * global variables
 * *********************************************************************/
 extern char maxSeqReach;
 extern int16_t connectionOpen;
 
/***********************************************************************
 * AT defines __USELESS __Examples for commande at max power
 * *********************************************************************/
#define COMMANDE_AT_DECOLLAGE    ",290718208\r" 
#define COMMANDE_AT_ATTERISSAGE    ",290717696\r" 
#define COMMANDE_AT_ARRET_URGENCE    ",290717952\r"
#define COMMANDE_AT_ANTI_ARRET_URGENCE    ",290717696\r"
#define COMMANDE_AT_AVANT    ",1,0,-1082130432,0,0\r" 
#define COMMANDE_AT_ARRIERE  ",1,0,1065353216,0,0\r" 
#define COMMANDE_AT_GAUCHE   ",1,-1082130432,0,0,0\r"
#define COMMANDE_AT_DROITE   ",1,1065353216,0,0,0\r" 
#define COMMANDE_AT_HAUT ",1,0,0,1065353216,0\r" 
#define COMMANDE_AT_BAS  ",1,0,0,-1082130432,0\r"
#define COMMANDE_AT_ROTATION_GAUCHE  ",1,0,0,0,-1082130432\r" 
#define COMMANDE_AT_ROTATION_DROITE  ",1,0,0,0,1065353216\r"
#define COMMANDE_CLOSE_CONNEC	"end_connection"

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

/***********************************************************************
 * Internal types
 * *********************************************************************/
 typedef enum cmd_type {
	 CMD_DECOLLAGE,
	 CMD_ATTERISSAGE,
	 CMD_ARRET_URGENCE,
	 CMD_ANTI_ARRET_URGENCE,
	 CMD_AVANT,
	 CMD_ARRIERE,
	 CMD_GAUCHE,
	 CMD_DROITE,
	 CMD_HAUT,
	 CMD_BAS,
	 CMD_ROTATION_GAUCHE,
	 CMD_ROTATION_DROITE,
	 CMD_CLOSE_CONNEC
} cmd_type ;

/***********************************************************************
 * Power Percentage
 * *********************************************************************/
typedef enum power_percent_type{
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
	} power_percent_type ;


/***********************************************************************
 * prototypes definitions
 * *********************************************************************/
 
int taking_off_AT() ;
int landing_AT() ;
int rising_AT(int times,power_percent_type percent) ;
int go_down_AT(int times,power_percent_type percent);
int turn_AT_Right(int times,power_percent_type percent) ;
int turn_AT_Left(int times,power_percent_type percent) ;
int go_forward_AT(int times,power_percent_type percent) ;
int go_back_AT(int times,power_percent_type percent) ;
int translate_right(int times,power_percent_type percent) ;
int translate_left(int times,power_percent_type percent) ;
int emergency_stop() ;
int no_emergency_stop() ;
int close_connect() ;

#ifdef __cplusplus
}
#endif
