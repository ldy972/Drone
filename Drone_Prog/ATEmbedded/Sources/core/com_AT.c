#include "com_AT.h"

//#define DEBUG

/*************************************************************************
 * Global Variables
 ***************************************************************************/
char maxSeqReached=0; // incrémenté si le numéro de séquence dépasse 9999
int16_t connectionOpen=0; // flag de connection au drone
int numSeq=0;		  // numéro de séquence à fournir à chaque envoi de commande AT
pthread_mutex_t mutex_AT_commands = PTHREAD_MUTEX_INITIALIZER;

/**
 * @overview : gestion du numéro de séquence
 * @arg :
 * @return :
 * @TODO : num sequence peut être une pointeur realloc, a chaque appel
 * */
void inc_num_sequence(void){
    ENTER_FCT()
    if (numSeq == 9999) {
        maxSeqReached++ ;
        numSeq=0 ;
    } else {
        numSeq++;
    }
    EXIT_FCT()
}

/**
 * @overview : convertir le type power_percentage en string null terminating
 * @arg : power_percentage pourcentage de puissance voulu ; 
 * @return : char* la chaine de charactère correspondant à la commande voulue
 * **/
char * convert_power(power_percentage power_p){

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

    inc_num_sequence();
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
char * build_AT_PCMD(int flag, power_percentage roll, power_percentage pitch, power_percentage gaz, power_percentage yaw)
{
    char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    inc_num_sequence();
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

    inc_num_sequence();
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

    inc_num_sequence();
    sprintf(returned_cmd, "AT*COMWDG=%i\r", numSeq);
    return returned_cmd;
}


/**
 * @overview : constructeur de commandes AT*CONFIG : configuration du drone. 
 * @arg : Pas d'options pour le moment, une seule config.
 * @return : 
 * **/
char* build_AT_CONFIG(char * config)
{
    char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    inc_num_sequence();
    sprintf(returned_cmd, "AT*CONFIG=%i,%s\r", numSeq, config);
    return returned_cmd;
} 

/**
 * @overview : constructeur de commandes AT*CTRL : envoi d'un ack 
 * @arg : Pas d'options pour le moment, une seule config.
 * @return : 
 * **/
char * build_AT_CTRL()
{
    char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    inc_num_sequence();
    sprintf(returned_cmd, "AT*CTRL=%d,0\r", numSeq);
    return returned_cmd;
} 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @overview : commandes du drone
 * @arg : la puissance de la commande
 * @return : 
 * **/

int send_AT_REF(AT_REF_cmd cmd){
    int result;

    pthread_mutex_lock(&mutex_AT_commands);
    char * command = build_AT_REF(cmd);

    result = send_message(command);
    pthread_mutex_unlock(&mutex_AT_commands);
    free(command);
    return result;
}

int take_off(void){
    int result = 0;
    int took_off = 0;

    while (!took_off) {
        result = send_AT_REF(REF_TAKE_OFF);
        pthread_mutex_lock(&mutex_navdata_struct);
        if (navdata_struct->navdata_option.altitude != 0) {
            took_off = 1;
        }
        pthread_mutex_unlock(&mutex_navdata_struct);
    }

    return result;
}

int land(void){
    int result = 0;
    int landed = 0;

    while (!landed) {
        result = send_AT_REF(REF_LAND);
        pthread_mutex_lock(&mutex_navdata_struct);
        if (navdata_struct->navdata_option.altitude == 0) {
            landed = 1;
        }
        pthread_mutex_unlock(&mutex_navdata_struct);
    }

    return result;
}

int reload_watchdog(void){
    int result;
    char * command = build_AT_COMWDG();

    result = send_message_no_delay(command);
    free(command);
    return result ;
}

int send_AT_PCMD(int flag, power_percentage roll, power_percentage pitch, power_percentage gaz, power_percentage yaw)
{
    int result;
    char * command = build_AT_PCMD(flag, roll, pitch, gaz, yaw);

    result = send_message(command);
    free(command);
    return result;
}

// pitch
int move_forward(power_percentage power){
    int result;

    result = send_AT_PCMD(1, 0, power, 0, 0);

    return result;
}

// yaw
int move_rotate(power_percentage power){
    int result;

    result = send_AT_PCMD(1, 0, 0, 0, power);

    return result;
}

// roll : negative to translate left, positive to translate right
int move_translate(power_percentage power){
    int result;

    result = send_AT_PCMD(1, power, 0, 0, 0);

    return result;
}

// gaz : positive = up, negative = down
int move_up_down(power_percentage power){
    int result;

    result = send_AT_PCMD(1, 0, 0, power, 0);

    return result;
}

// Enter and exit emergency mode
// TODO : Maybe check Emergency mode flag in navdata state
int emergency_stop(void){
    return send_AT_REF(REF_EMERGENCY_STOP);
}

int no_emergency_stop(void){
    return send_AT_REF(REF_NO_EMERGENCY);
}

int configure_navdata()
{
    int result;
    char * config = malloc(TAILLE_COMMANDE * sizeof(char));
    sprintf(config, "%s", NAVDATA_DEMO_CONFIG);
    char * command = build_AT_CONFIG(config);

    result = send_message(command);
    free(config);
    free(command);
    return result;
}

int send_ack_message()
{
    int result;
    char * command = build_AT_CTRL();

    result = send_message(command);
    free(command);
    return result;
}

int trim_sensors()
{
    int result;
    char * command = build_AT_FTRIM();

    result = send_message(command);
    free(command);
    return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * initialize_connection_with_drone : Opens the sockets and triggers navdata sending by the drone
 * @arg : void
 * @return : status 0 = OK
 * **/
int initialize_connection_with_drone(void)
{
    ENTER_FCT()
    int result;

    PRINT_LOG("Init");
    // Open AT_Commands and navdata socket
    result = initialize_commands_socket();
    connectionOpen = 1;
    PRINT_LOG("Init OK");

    EXIT_FCT();
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

power_percentage get_power(int power)
{
    power_percentage result;

    switch (power) {
    case -100:
        result = NEG_POWER_100;
        break;
    case -75:
        result = NEG_POWER_75;
        break;
    case -50:
        result = NEG_POWER_50;
        break;
    case -25:
        result = NEG_POWER_25;
        break;
    case -20:
        result = NEG_POWER_20;
        break;
    case -10:
        result = NEG_POWER_10;
        break;
    case -5:
        result = NEG_POWER_5;
        break;
    case 5:
        result = POS_POWER_5;
        break;
    case 10:
        result = POS_POWER_10;
        break;
    case 20:
        result = POS_POWER_20;
        break;
    case 25:
        result = POS_POWER_25;
        break;
    case 50:
        result = POS_POWER_50;
        break;
    case 75:
        result = POS_POWER_75;
        break;
    case 100:
        result = POS_POWER_100;
        break;
    default:
        result = NULL_POWER_VALUE;
        break;
    }

    return result;
}


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
    power_percentage pow = get_power(power);

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
    power_percentage pow = get_power(-power);

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
    power_percentage pow = get_power(power);

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
    power_percentage pow = get_power(-power);

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
    power_percentage pow = get_power(-power);

    while (i>=0){
        move_forward(pow);       
        i--;
    }
    return 0;
}

/**
 *backward : move backwards
 *@arg : int power, int time : power of the command, number of command to send
 *@return : status = 0 : OK
 **/

int backward(int power, int time){
    int i = time;
    power_percentage pow = get_power(power);

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
    power_percentage pow = get_power(power);

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
    power_percentage pow = get_power(-power);

    while (i>=0){
        move_up_down(pow);       
        i--;
    }
    return 0;
}
