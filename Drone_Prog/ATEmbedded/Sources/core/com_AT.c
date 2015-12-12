#include "com_AT.h"

//#define DEBUG

/*************************************************************************
* Global Variables
***************************************************************************/
char maxSeqReach=0; // incrémenté si le numéro de séquence dépasse 9999
int16_t connectionOpen=0; // flag de connection au drone
char *numSequence = NULL; //ascii 48 = '0'
int numSeq=0;		  // numéro de séquence à fournir à chaque envoi de commande AT

/**
 * @overview : gestion du numéro de séquence
 * @arg :
 * @return :
 * @TODO : num sequence peut être une pointeur realloc, a chaque appel
 * */
 void inc_num_sequence(void){
     ENTER_FCT()
     int taille = 0 ;
     if(numSeq==9999){
         maxSeqReach++ ;
         numSeq=0 ;
     }
     if(numSequence!=NULL)
        free(numSequence) ;
    numSequence = (char*)calloc(5,sizeof(char)) ;
    numSequence[4]='\0' ; // Null terminating string
	sprintf(numSequence,"%d",++numSeq) ;
    taille = strlen(numSequence);
    numSequence = (char*)realloc(numSequence,taille*sizeof(char)) ;
	EXIT_FCT()
 }

/**
 * @overview : convertir le type power_percent en string null terminating
 * @arg : power_percent pourcentage de puissance voulu ; 
 * @return : char* la chaine de charactère correspondant à la commande voulue
 * **/
char * convert_power(power_percent power_p){
	 
    char tmp[POWER_P_SIZE+1];
	tmp[POWER_P_SIZE] = '\0' ;

	sprintf(tmp,"%i",power_p) ;

	return strdup(tmp) ;
}

/**
 * @overview : constructeur de commandes AT*REF : decollage, aterrissage, arret d'urgence, anti-urgence
 * @arg : la commande AT_REF utilisée
 * @return : 
 * **/
char * build_AT_REF (AT_REF_cmd cmd)
{
	char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    numSeq ++;
	switch(cmd){
		case REF_TAKE_OFF:
		sprintf(returned_cmd, "%s%i,290718208\r", H_AT_REF, numSeq);
		break;

		case REF_LAND:
		sprintf(returned_cmd, "%s%i,290717696\r", H_AT_REF, numSeq);
		break;

		case REF_EMERGENCY_STOP:
		sprintf(returned_cmd, "%s%i,290717952\r", H_AT_REF, numSeq);
		break;

		case REF_NO_EMERGENCY:
		sprintf(returned_cmd, "%s%i,290717696\r", H_AT_REF, numSeq);
		break;}
	return returned_cmd;
}


/**
 * @overview : constructeur de commandes AT*PCMD : déplacements du drone
 * @arg : le hovering flag et les valeurs en pourcentage puissance moteur des déplacement
 * @return : 
 * **/
char * build_AT_PCMD(int flag, power_percent roll, power_percent pitch, power_percent gaz, power_percent yaw)
{
	char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    numSeq++;
	sprintf(returned_cmd, "AT*PCMD=%i,%i,%i,%i,%i,%i\r", numSeq, flag, (int)roll, (int)pitch, (int)gaz, (int)yaw);
	return returned_cmd;
}


/**
 * @overview : constructeur de commandes AT*FTRIM : calibrage du drone
 * @arg : 
 * @return : 
 * **/
char * build_AT_FTRIM()
{
	char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    numSeq++;
	sprintf(returned_cmd, "%s%i\r",H_AT_FTRIM, numSeq);
	return returned_cmd;
}


/**
 * @overview : constructeur de commandes AT*COMWDG : reload du watchdog
 * @arg : 
 * @return : 
 * **/
char * build_AT_COMWDG(void)
{
	char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    numSeq++;
	sprintf(returned_cmd, "AT*COMWDG=%i\r", numSeq);
	return returned_cmd;
}


/**
 * @overview : constructeur de commandes AT*CONFIG : configuration du drone. 
 * @arg : Pas d'options pour le moment, une seule config.
 * @return : 
 * **/
char* build_AT_CONFIG(void)
{
	char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    numSeq++;
	sprintf(returned_cmd, "AT*CONFIG=%i,%s", numSeq, COMMANDE_AT_GET_NAV_DATA);
	return returned_cmd;
} 

/**
 * @overview : constructeur de commandes AT*CTRL : envoi d'un ack 
 * @arg : Pas d'options pour le moment, une seule config.
 * @return : 
 * **/
char * build_AT_ACK(void)
{
	char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    numSeq++;
	sprintf(returned_cmd, "AT*CTRL=%d,0\r", numSeq);
	return returned_cmd;
} 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @overview : commandes du drone
 * @arg : la puissance de la commande
 * @return : 
 * **/

int take_off(void){
    int result;
    char * command = build_AT_REF(REF_TAKE_OFF);

    result = send_message(command);
    free(command);
    return result;
}

int land(void){
    int result;
    char * command = build_AT_REF(REF_LAND);

    result = send_message(command);
    free(command);
    return result;
}

int reload_watchdog(void){
	return send_message(build_AT_COMWDG());
}

// pitch
int move_forward(power_percent power){
	return send_message(build_AT_PCMD(1,0,power,0,0));
}

// yaw
int move_rotate(power_percent power){
	return send_message(build_AT_PCMD(1,0,0,0,power));
}

// roll : negative to translate left, positive to translate right
int move_translate(power_percent power){
	return send_message(build_AT_PCMD(1,power,0,0,0));
}

// gaz : positive = up, negative = down
int move_up_down(power_percent power){
	return send_message(build_AT_PCMD(1,0,0,power,0));
}

int emergency_stop(void){
    int result;
    char * command = build_AT_REF(REF_EMERGENCY_STOP);

    result = send_message(command);
    free(command);
    return result;
}

int no_emergency_stop(void){
    int result;
    char * command = build_AT_REF(REF_NO_EMERGENCY);

    result = send_message(command);
    free(command);
    return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ENVOI DE MESSAGES AU DRONE

int send_navdata_config(void){
	return send_message(build_AT_CONFIG());
}

int send_ack(void){
	return send_message(build_AT_ACK());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**
 * initialize_connection_with_drone : Opens the sockets and triggers navdata sending by the drone
 * @arg : void
 * @return : status 0 = OK
 * **/
int initialize_connection_with_drone(void)
{
    ENTER_FCT()
    int result;
    char command[MAX_BUF_LEN];

    PRINT_LOG("Init");
    // Open AT_Commands and navdata socket
    result = initialize_sockets();
    connectionOpen = 1;
    PRINT_LOG("Init OK");

    // If both succeeded, ask the drone to send navdata
    if (result == 0) {
        // Send special message to navdata port
        sprintf(command, NAVDATA_INIT_MSG);
        PRINT_LOG("Send push");
        result = send_navdata("\x01\x00");
        PRINT_LOG("Push sent");
        DELAY(40000)

        // Set navdata configuration
        if (result == 0) {
            PRINT_LOG("Send conf");
            send_navdata_config();
            PRINT_LOG("Conf sent");
            DELAY(40000)
        }

        // Send ACK
        if (result == 0) {
            PRINT_LOG("Send ack");
            result = send_ack();
            PRINT_LOG("Ack sent");
        }

        // Close navdata socket
        if (result == 0) {
            PRINT_LOG("Close nav");
            result = close_navdata_socket();
            PRINT_LOG("Close nav");
        }
    }

    EXIT_FCT();
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	Fonctions globales a utiliser par la commande finale

*/


/**
 *rotate_right : rotate the drone to the right
 *@arg : int power : power or the command (0,5,10,20,25,50,75,100)
 *@arg : int time : number of rotation
 *@return : status = 0 : OK 
**/

int rotate_right(int power, int time){
	int i = time;
	power_percent pow;
	switch (power){
		case 0 : pow = NULL_POWER_VALUE; break;
		case 5 : pow = POS_POWER_5_; break;
		case 10 : pow = POS_POWER_10_; break;
		case 20 : pow = POS_POWER_20_; break;
		case 25 : pow = POS_POWER_25_; break;
		case 50 : pow = POS_POWER_50_; break;
		case 75 : pow = POS_POWER_75_; break;
		case 100 : pow = POS_POWER_100_; break;
		default : pow = NULL_POWER_VALUE; break;
	}
	
	while (i>=0){
		move_rotate(pow);	
		i--;
	}
	return 0;
}

/**
 *rotate_left : rotate the drone to the left
 *@arg : int power : power or the command (0,5,10,20,25,50,75,100)
 *@arg : int time : number of rotation
 *@return : status = 0 : OK 
**/

int rotate_left(int power, int time){
        int i = time;
        power_percent pow;
        switch (power){
                case 0 : pow = NULL_POWER_VALUE; break;
                case 5 : pow = NEG_POWER_5_; break;
                case 10 : pow = NEG_POWER_10_; break;
                case 20 : pow = NEG_POWER_20_; break;
                case 25 : pow = NEG_POWER_25_; break;
                case 50 : pow = NEG_POWER_50_; break;
                case 75 : pow = NEG_POWER_75_; break;
                case 100 : pow = NEG_POWER_100_; break;
                default : pow = NULL_POWER_VALUE; break;
        }

        while (i>=0){
                move_rotate(pow);       
                i--;
        }
        return 0;
}


/**
 *translate_right : translate the drone to the right
 *@arg : int power : power or the command (0,5,10,20,25,50,75,100)
 *@arg : int time : number of translation
 *@return : status = 0 : OK 
**/

int translate_right(int power, int time){
        int i = time;
        power_percent pow;
        switch (power){
                case 0 : pow = NULL_POWER_VALUE; break;
                case 5 : pow = POS_POWER_5_; break;
                case 10 : pow = POS_POWER_10_; break;
                case 20 : pow = POS_POWER_20_; break;
                case 25 : pow = POS_POWER_25_; break;
                case 50 : pow = POS_POWER_50_; break;
                case 75 : pow = POS_POWER_75_; break;
                case 100 : pow = POS_POWER_100_; break;
                default : pow = NULL_POWER_VALUE; break;
        }

        while (i>=0){
                move_translate(pow);       
                i--;
        }
        return 0;
}

/**
 *translate_left : translate the drone to the left
 *@arg : int power : power or the command (0,5,10,20,25,50,75,100)
 *@arg : int time : number of translation
 *@return : status = 0 : OK 
**/

int translate_left(int power, int time){
        int i = time;
        power_percent pow;
        switch (power){
                case 0 : pow = NULL_POWER_VALUE; break;
                case 5 : pow = NEG_POWER_5_; break;
                case 10 : pow = NEG_POWER_10_; break;
                case 20 : pow = NEG_POWER_20_; break;
                case 25 : pow = NEG_POWER_25_; break;
                case 50 : pow = NEG_POWER_50_; break;
                case 75 : pow = NEG_POWER_75_; break;
                case 100 : pow = NEG_POWER_100_; break;
                default : pow = NULL_POWER_VALUE; break;
        }

        while (i>=0){
                move_translate(pow);       
                i--;
        }
        return 0;
}

/**
 *forward : move forward
 *@arg : int power, int time : power of the command, number of command to send
 *@return : status = 0 : OK
**/

int forward(int power, int time){
	int i = time;
        power_percent pow;
        switch (power){
                case 0 : pow = NULL_POWER_VALUE; break;
                case 5 : pow = POS_POWER_5_; break;
                case 10 : pow = POS_POWER_10_; break;
                case 20 : pow = POS_POWER_20_; break;
                case 25 : pow = POS_POWER_25_; break;
                case 50 : pow = POS_POWER_50_; break;
                case 75 : pow = POS_POWER_75_; break;
                case 100 : pow = POS_POWER_100_; break;
                default : pow = NULL_POWER_VALUE; break;
        }

        while (i>=0){
                move_forward(pow);       
                i--;
        }
        return 0;
}

/**
 *up : move up
 *@arg : int power, int time : power of the command, number of command to send
 *@return : status = 0 : OK
**/

int up(int power, int time){
        int i = time;
        power_percent pow;
        switch (power){
                case 0 : pow = NULL_POWER_VALUE; break;
                case 5 : pow = POS_POWER_5_; break;
                case 10 : pow = POS_POWER_10_; break;
                case 20 : pow = POS_POWER_20_; break;
                case 25 : pow = POS_POWER_25_; break;
                case 50 : pow = POS_POWER_50_; break;
                case 75 : pow = POS_POWER_75_; break;
                case 100 : pow = POS_POWER_100_; break;
                default : pow = NULL_POWER_VALUE; break;
        }

        while (i>=0){
                move_up_down(pow);       
                i--;
        }
        return 0;
}

/**
 *down : move down
 *@arg : int power, int time : power of the command, number of command to send
 *@return : status = 0 : OK
**/

int down(int power, int time){
        int i = time;
        power_percent pow;
        switch (power){
                case 0 : pow = NULL_POWER_VALUE; break;
                case 5 : pow = NEG_POWER_5_; break;
                case 10 : pow = NEG_POWER_10_; break;
                case 20 : pow = NEG_POWER_20_; break;
                case 25 : pow = NEG_POWER_25_; break;
                case 50 : pow = NEG_POWER_50_; break;
                case 75 : pow = NEG_POWER_75_; break;
                case 100 : pow = NEG_POWER_100_; break;
                default : pow = NULL_POWER_VALUE; break;
        }

        while (i>=0){
                move_up_down(pow);       
                i--;
        }
        return 0;
}
