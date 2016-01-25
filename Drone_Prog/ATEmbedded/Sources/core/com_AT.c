#include "com_AT.h"

//#define DEBUG

/******************************************************************************
 * Global Variables                                                           *
 *****************************************************************************/

char maxSeqReached=0; // incrémenté si le numéro de séquence dépasse 9999
int16_t connectionOpen=0; // flag de connection au drone
int numSeq=0;		  // numéro de séquence à fournir à chaque envoi de commande AT
pthread_mutex_t mutex_AT_commands = PTHREAD_MUTEX_INITIALIZER;

// Min and max values for drone heading, used to rectify the value
int flag_set_heading_range = 0;
float min_heading;
float max_heading;

/******************************************************************************
 * Local functions prototypes                                                 *
 *****************************************************************************/

// Misc functions
void inc_num_sequence();
int convert_power(float power);
int convert_angle_to_power(float angle);
float get_power(int power);

// AT Commands builders
char * build_AT_REF(AT_REF_cmd cmd);
char * build_AT_PCMD(int flag, float roll, float pitch, float gaz, float yaw);
char * build_AT_PCMD_MAG(int flag, float roll, float pitch, float gaz, float yaw, float heading, float heading_accuracy);
char * build_AT_FTRIM();
char * build_AT_COMWDG();
char * build_AT_CONFIG();
char * build_AT_CTRL();
char * build_AT_CALIB(int device_id);

// AT Commands senders
int send_AT_REF(AT_REF_cmd cmd);
int send_AT_PCMD(int flag, float roll, float pitch, float gaz, float yaw);
int send_AT_PCMD_MAG(int flag, float roll, float pitch, float gaz, float yaw, float heading, float heading_accuracy);
int send_AT_CALIB(int device_id);
int configure_navdata(char * parameter, char * value);


/******************************************************************************
 * Local functions declarations : Misc                                        *
 *****************************************************************************/

/**
 * @overview : gestion du numéro de séquence
 * @arg :
 * @return :
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

// Converts a float value in range [-1.0;1.0] to the corresponding value for AT commands
int convert_power(float power)
{
    if (abs(power) > 1.0)
    {
        // Invalid input, set result to 0
        return 0;
    } else {
        // Get the content of power, interpreted as an int instead of a float
        return *(int *) (&power);
    }
}


// Converts an angle in range [-180°;180°] to the corresponding value for AT commands
int convert_angle_to_power(float angle)
{
    int turns = (int) (angle / 360.0);
    return convert_power((angle - (float) (turns * 360)) / 180.0);
}

// Converts a power value between -100 and 100 t the corresponding power percentage
float get_power(int power)
{
    return ((float) power) / 100.0;
}

/******************************************************************************
 * Local functions declarations : AT Builders                                 *
 *****************************************************************************/

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
char * build_AT_PCMD(int flag, float roll, float pitch, float gaz, float yaw)
{
    char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    inc_num_sequence();
    sprintf(returned_cmd, "AT*PCMD=%i,%i,%i,%i,%i,%i\r", numSeq, flag, convert_power(roll), convert_power(pitch), convert_power(gaz), convert_power(yaw));
    return returned_cmd;
}


/**
 * @overview : constructeur de commandes AT*PCMD : déplacements du drone
 * @arg : le hovering flag et les valeurs en pourcentage puissance moteur des déplacement
 * @return :
 * **/
char * build_AT_PCMD_MAG(int flag, float roll, float pitch, float gaz, float yaw, float heading, float heading_accuracy)
{
    char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    inc_num_sequence();
    sprintf(returned_cmd, "AT*PCMD_MAG=%i,%i,%i,%i,%i,%i,%i,%i\r", numSeq, flag, convert_power(roll), convert_power(pitch), convert_power(gaz), convert_power(yaw), convert_angle_to_power(heading), convert_power(heading_accuracy));
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
char* build_AT_CONFIG(char * parameter, char * value)
{
    char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    inc_num_sequence();
    sprintf(returned_cmd, "AT*CONFIG=%i,\"%s\",\"%s\"\r", numSeq, parameter, value);
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

char * build_AT_CALIB(int device_id)
{
    char * returned_cmd = (char *) malloc(TAILLE_COMMANDE * sizeof(char));

    inc_num_sequence();
    sprintf(returned_cmd, "AT*CALIB=%d,%d\r", numSeq, device_id);
    return returned_cmd;

}


/******************************************************************************
 * Local functions declarations : AT Senders                                  *
 *****************************************************************************/

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


int send_AT_PCMD(int flag, float roll, float pitch, float gaz, float yaw)
{
    int result;
    char * command = build_AT_PCMD(flag, roll, pitch, gaz, yaw);

    result = send_message(command);
    free(command);
    return result;
}

int send_AT_PCMD_MAG(int flag, float roll, float pitch, float gaz, float yaw, float heading, float heading_accuracy)
{
    int result;
    char * command = build_AT_PCMD_MAG(flag, roll, pitch, gaz, yaw, heading, heading_accuracy);

    result = send_message(command);
    free(command);
    return result;
}


int send_AT_CALIB(int device_id)
{
    int result;
    char * command = build_AT_CALIB(device_id);

    result = send_message(command);
    free(command);
    return result;
}

int configure_navdata(char * parameter, char * value)
{
    int result;
    char * command = build_AT_CONFIG(parameter, value);

    result = send_message(command);
    free(command);

    return result;
}



/******************************************************************************
 * Functions declarations                                                     *
 *****************************************************************************/

// Intermediary functions for classic movement

// pitch
int move_forward(float power){
    int result;

    result = send_AT_PCMD(1, 0, power, 0, 0);

    return result;
}

// yaw
int move_rotate(float power){
    int result;

    result = send_AT_PCMD(1, 0, 0, 0, power);

    return result;
}

// roll : negative to translate left, positive to translate right
int move_translate(float power){
    int result;

    result = send_AT_PCMD(1, power, 0, 0, 0);

    return result;
}

// gaz : positive = up, negative = down
int move_up_down(float power){
    int result;

    result = send_AT_PCMD(1, 0, 0, power, 0);

    return result;
}

// Intermediary functions for movement with the magnetometer

// Pitch
int move_forward_mag(float power, float heading){
    int result;

    result = send_AT_PCMD_MAG(5, 0, power, 0, 0, heading, 0.02);
    return result;
}

// Roll
int move_translate_mag(float power, float heading){
    int result;

    result = send_AT_PCMD_MAG(5, power, 0, 0, 0, heading, 0.02);

    return result;
}

// Yaw
int move_rotate_mag(float power, float heading){
    int result;

    result = send_AT_PCMD_MAG(0, 0, 0, 0, power, heading, 0.02);

    return result;
}


// Taking off, landing and emregency mode

/**
 *take_off : Makes the drone take off
 *@arg :
 *@return : status = 0 : OK
 **/
int take_off(void) {
    int result = 0;
    int took_off = 0;

    while (!took_off) {
        result = send_AT_REF(REF_TAKE_OFF);
        if (get_altitude() != 0) {
            took_off = 1;
        }
    }

    return result;
}

/**
 *land : Makes the drone land
 *@arg :
 *@return : status = 0 : OK
 **/
int land(void){
    int result = 0;
    int landed = 0;

    while (!landed) {
        result = send_AT_REF(REF_LAND);
        if (get_altitude() == 0) {
            landed = 1;
        }
    }

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

/**
 *reload_watchdog : Reloads the watchdog
 *@arg :
 *@return : status = 0 : OK
 **/
int reload_watchdog(void){
    int result;
    char * command = build_AT_COMWDG();

    result = send_message_no_delay(command);
    free(command);
    return result ;
}


// Classic controls

int hover()
{
    int result;

    result = send_AT_PCMD(1, 0.0, 0.0, 0.0, 0.0);

    return result;

}

/**
 *rotate_right : rotate the drone to the right
 *@arg : int power : power or the command (0,5,10,20,25,50,75,100)
 *@arg : float aimed_angle : angle aimed to rotate
 *@return : status = 0 : OK 
 **/


int rotate_right(int power, float angle_disp) //angle_disp = angle_displacement = relative displacement wished 
{
    float current_angle = get_yaw() ;

    float pow = get_power(power);
    float aimed_angle = (current_angle + angle_disp) ; 
    int i = 0 ;

    if(aimed_angle>=360.0)
        aimed_angle = aimed_angle-360.0 ; 

    else if(aimed_angle < 0.0)
        aimed_angle = aimed_angle+360.0 ;

    printf("aimed_angle = %f\n",aimed_angle);

    if(angle_disp == 360.0)
    { 
        for(i=0;i<20;i++)
        {
            move_rotate(pow) ;
            current_angle = get_yaw() ;
        }   
    }

    if(aimed_angle == 360.0 || aimed_angle == 0.0)
    {    
        while(current_angle < 359.0 && current_angle > 1.0)
        {
            move_rotate(pow) ;
            current_angle = get_yaw() ;
        }
    }
    else 
    {
        while(abs(aimed_angle-current_angle) >= 4.0)
        {   
            move_rotate(pow) ;
            current_angle = get_yaw() ;
        }
    }
    move_rotate(0.1) ;

    return 0 ;
}


/**
 *rotate_left : rotate the drone to the left
 *@arg : int power : power or the command (0,5,10,20,25,50,75,100)
 *@arg : float aimed_angle : angle aimed to rotate
 *@return : status = 0 : OK
 **/

int rotate_left(int power, float angle_disp) //angle_disp = angle_displacement = relative displacement wished 
{
    float current_angle = get_yaw() ;
    float pow = get_power(-power);
    float aimed_angle = (current_angle + angle_disp) ; 
    int i = 0 ;

    if(aimed_angle>=360.0)
        aimed_angle = aimed_angle-360.0 ; 

    else if(aimed_angle < 0.0)
        aimed_angle = aimed_angle+360.0 ;

    printf("aimed_angle = %f\n",aimed_angle);

    if(angle_disp == 360.0)
    { 
        for(i=0;i<20;i++)
        {
            move_rotate(pow) ;
            current_angle = get_yaw() ;
        }   
    }

    if(aimed_angle == 360.0 || aimed_angle == 0.0)
    {    
        while(current_angle < 359.0 && current_angle > 1.0)
        {
            move_rotate(pow) ;
            current_angle = get_yaw() ;
        }
    }
    else 
    {
        while(abs(aimed_angle-current_angle) >= 4.0)
        {   
            move_rotate(pow) ;
            current_angle = get_yaw() ;
        }
    }
    move_rotate(-0.1);

    return 0 ;
}



int translate_right(int power, float aimed_distance)
{
    float passed_distance = 0.0 ;
    float t0 = 0.0, t1 = 0.0 ;
    float pow = get_power(power);

    while (passed_distance < aimed_distance)
    {
        t0 = (float)(clock()/CLOCKS_PER_SEC) ; 
        move_translate(pow) ;
        t1 = (float)(clock()/CLOCKS_PER_SEC) ;
        passed_distance = passed_distance + get_vx()*(t1-t0) ;
    }
    return 0 ;
}

/**
 *translate_left : translate the drone to the left
 *@arg : int power : power or the command (0,5,10,20,25,50,75,100)
 *@arg : float aimed_distance : distance wanted to translate
 *@return : status = 0 : OK 
 **/

int translate_left(int power, float aimed_distance)
{
    float passed_distance = 0.0 ;
    float t0 = 0.0, t1 = 0.0 ;
    float pow = get_power(-power);

    while (passed_distance > aimed_distance)
    {
        t0 = (float)(clock()/CLOCKS_PER_SEC) ; 
        move_translate(pow) ;
        t1 = (float)(clock()/CLOCKS_PER_SEC) ;
        passed_distance = passed_distance + get_vx()*(t1-t0) ;
    }

    return 0 ;
}


/**
 *forward : move forward
 *@arg : int power : power of the command
 *@arg : float aimed_distance : distance wanted to go forward
 *@return : status = 0 : OK
 **/

int forward(int power, float aimed_distance)
{  
    struct timespec instant ;
    struct timespec instant_next ;
    float passed_distance = 0.0, vx = 0.0 ;
    float pow = get_power(-power);

    while (passed_distance < aimed_distance * 1000.0)
    {
        printf("passed distance : %f\n", passed_distance) ;
        clock_gettime(CLOCK_MONOTONIC, &instant) ;

        printf("t0 : %ld\n", instant.tv_nsec) ;
        move_forward(pow) ;
        vx = get_vx() ;
        printf("speed : %f\n",vx);
        clock_gettime(CLOCK_MONOTONIC, &instant_next);
        printf("t1 : %ld\n", instant_next.tv_nsec) ;
        passed_distance = passed_distance + vx * ((float)(instant_next.tv_nsec - instant.tv_nsec) / 1000000.0);
    }

    return 0 ;
}
/**
 *backward : move backwards
 *@arg : int power : power of the command
 *@arg : float aimed_distance : distance wanted to go backward
 *@return : status = 0 : OK
 **/
int backward(int power, float aimed_distance)
{

    float passed_distance = 0.0 ;
    float t0 = 0.0, t1 = 0.0 ;
    float pow = get_power(power);

    while (passed_distance > aimed_distance)
    {
        t0 = (float)(clock()/CLOCKS_PER_SEC) ;
        move_translate(pow) ;
        t1 = (float)(clock()/CLOCKS_PER_SEC) ;
        passed_distance = passed_distance + get_vy()*(t1-t0) ;
    }

    return 0 ;

}

/**
 *up : move up
 *@arg : int power : power of the command
 *@arg : float aimed_height : height wanted to go up
 *@return : status = 0 : OK
 **/
int up(int power, float aimed_height)
{
    float altitude = get_altitude() ;
    float pow = get_power(power);
    while (altitude<=aimed_height)
    {
        move_up_down(pow);  
        altitude = get_altitude() ;     
    }

    return 0;
}


/**
 *down : move down
 *@arg : int power : power of the command
 *@arg : float aimed_height : height wanted to go up
 *@return : status = 0 : OK
 **/

int down(int power, float aimed_height)
{
    float altitude = get_altitude() ;
    float pow = get_power(-power);
    while (altitude>=aimed_height)
    {
        move_up_down(pow); 
        altitude = get_altitude() ;      
    }

    return 0;
}


// Controls with magnetometer

/**
 *rotate_right_mag : rotate the drone to the right
 *@arg : int power : power or the command (0,5,10,20,25,50,75,100)
 *@arg : int time : number of rotation
 *@arg : float heading : the heading the drone must follow
 *@return : status = 0 : OK 
 **/

int rotate_right_mag(int power, float heading_disp)
{
    float pow = get_power(power);
    float current_heading = get_heading() ;
    float aimed_heading = current_heading + heading_disp ;

    while (current_heading<aimed_heading)
    {
        move_rotate_mag(pow, current_heading) ;
        current_heading = get_heading() ;
        printf("heading : %f\n", current_heading);
    }

   move_rotate_mag(-pow/10.0, current_heading);

    return 0;
}


/**
 *rotate_left_mag : rotate the drone to the left
 *@arg : int power : power or the command (0,5,10,20,25,50,75,100)
 *@arg : int time : number of rotation
 *@arg : float heading : the heading the drone must follow
 *@return : status = 0 : OK 
 **/

int rotate_left_mag(int power, float heading_disp)
{
    float pow = get_power(-power);
    float current_heading = get_heading() ;
    float aimed_heading = current_heading - heading_disp ;


    while (current_heading>aimed_heading)
    {
        move_rotate_mag(pow, current_heading) ;
        current_heading = get_heading() ;
        printf("heading : %f\n", current_heading);
    }


    move_rotate_mag(pow, current_heading);


    return 0;
}

/**
 *orientate_mag : orientate the drone to an absolute heading going right
 *@arg : int power : power or the command (0,5,10,20,25,50,75,100)
 *@arg : int time : number of rotation
 *@arg : float heading : the heading the drone must follow
 *@return : status = 0 : OK 
 **/

int orientate_mag(int motor_pow, float aimed_heading)
{
    int current_heading = ((int)(get_heading()))%360 ; //Marche aussi pour un heading <0
    if(current_heading < 0) {
        current_heading += 360;
    }
    //un cap int absolu ramené entre 0 et 360, ququelquesoit le cap de départ
    printf("Cap ramené : %d\n",current_heading);  

    if(current_heading<=(int)aimed_heading) {  
        printf("Cap courant <= au cap souhaité\n") ;

        if(((int)aimed_heading-current_heading) >= 180) {     
            printf("cap souhaité à plus de 180° du cap courant : on part à gauche \n"); 
            rotate_left_mag(motor_pow, 360-((int)aimed_heading-current_heading)) ;
            current_heading = (int)(get_heading())%360 ;
            if(current_heading < 0)
                current_heading += 360 ;  
        } else {    
            printf("cap souhaité à moins de 180° du cap courant : on part à droite \n");  
            rotate_right_mag(motor_pow, (int)aimed_heading-current_heading);
            current_heading = (int)(get_heading())%360 ;
            if(current_heading < 0)
                current_heading += 360 ;
        }
    } else { 
        printf("cap courant > cap souhaité\n");  
        if ((current_heading - (int) aimed_heading) <= 180) { 
            printf("différence à moins de 180° : on parcourt %d degrés sur la gauche\n",current_heading-(int)aimed_heading);
            rotate_left_mag(motor_pow, (current_heading-(int)aimed_heading));
            current_heading = (int)(get_heading())%360 ;
            if(current_heading < 0) {
                current_heading += 360 ;
            }
        } else {
            printf("différence à plus  de 180° : on parcourt %d degrés sur la droite\n",(360-(current_heading - (int)aimed_heading)));
            rotate_right_mag(motor_pow, 360-(current_heading-(int)aimed_heading));
            current_heading = (int)(get_heading())%360 ;
            if(current_heading < 0) {
                current_heading += 360 ;
            }
        } 
    }

    return 0 ;

}

/**
 *translate_right_mag : translate the drone to the right
 *@arg : int power : power or the command (0,5,10,20,25,50,75,100)
 *@arg : int time : number of translation
 *@arg : float heading : the heading the drone must follow
 *@return : status = 0 : OK 
 **/
int translate_right_mag(int power, int times, float heading)
{
    int i = times;
    float pow = get_power(power);

    while (i>=0)
    {
        move_translate_mag(convert_power(pow), heading);
        i--;
    }
    return 0;
}

/**
 *translate_left_mag : translate the drone to the left
 *@arg : int power : power or the command (0,5,10,20,25,50,75,100)
 *@arg : int time : number of translation
 *@arg : float heading : the heading the drone must follow
 *@return : status = 0 : OK 
 **/
int translate_left_mag(int power, int times, float heading)
{
    int i = times;
    float pow = get_power(-power);

    while (i>=0)
    {
        move_translate_mag(convert_power(pow), heading);
        i--;
    }
    return 0;
}

/**
 *forward_mag : move forward
 *@arg : int power, int time : power of the command, number of command to send
 *@arg : float heading : the heading the drone must follow
 *@return : status = 0 : OK
 **/
int forward_mag(int power, int times, float heading)
{
    int i = times;
    float pow = get_power(-power);

    while (i>=0)
    {
        move_forward_mag(convert_power(pow), heading);
        i--;
    }
    move_forward_mag(convert_power(-pow),heading);
    return 0;
}

/**
 *backward_mag : move backwards
 *@arg : int power, int time : power of the command, number of command to send
 *@arg : float heading : the heading the drone must follow
 *@return : status = 0 : OK
 **/
int backward_mag(int power, int times, float heading){
    int i = times;
    float pow = get_power(power);

    while (i>=0){
        move_forward_mag(convert_power(pow), heading);
        i--;
    }
    return 0;
}


// Messages used for initialization

int configure_navdata_demo()
{
    int result;
    char * param = malloc(TAILLE_COMMANDE * sizeof(char));
    char * value = malloc(TAILLE_COMMANDE * sizeof(char));
    sprintf(param, "%s", NAVDATA_DEMO_PARAM);
    sprintf(value, "%s", NAVDATA_DEMO_VALUE);

    result = configure_navdata(param, value);

    free(param);
    free(value);
    return result;
}

int configure_navdata_magneto()
{
    int result;
    char * param = malloc(TAILLE_COMMANDE * sizeof(char));
    char * value = malloc(TAILLE_COMMANDE * sizeof(char));
    int options = 0x01 << option_demo | 0x01 << option_magneto;
    sprintf(param, "%s", NAVDATA_MAGNETO_PARAM);
    sprintf(value, "%d", options);

    result = configure_navdata(param, value);

    free(param);
    free(value);
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


int calibrate_magnetometer()
{
    int result;

    result = send_AT_CALIB(0);

    return result;
}


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

