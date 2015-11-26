#include "com.h"

#define DEBUG

/*************************************************************************
* Global Variables
***************************************************************************/
char maxSeqReach=0;
int16_t connectionOpen=0;
char *numSequence = NULL; //ascii 48 = '0'
int numSeq=0;

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
 * @overview : convertir le type power_percent_type en string null terminating
 * @arg : power_percent_type pourcentage voulu ; 
 * @return : char* la chaine de charactère correspondant à la commande voulue
 * **/
 char* convert_power(power_percent_type power_p){
	 
		char tmp[POWER_P_SIZE+1];
		tmp[POWER_P_SIZE] = '\0' ;
		switch(power_p){
			case POS_POWER_5_ :
				sprintf(tmp,"%i",POS_POWER_5_) ;
				break;
			case POS_POWER_10_ :
				sprintf(tmp,"%i",POS_POWER_10_) ;
				break;
			case POS_POWER_20_ :
				sprintf(tmp,"%i",POS_POWER_20_) ;
				break;
			case POS_POWER_25_ :
				sprintf(tmp,"%i",POS_POWER_25_) ;
				break;
			case POS_POWER_50_ :
				sprintf(tmp,"%i",POS_POWER_50_) ;
				break;
			case POS_POWER_75_ :
				sprintf(tmp,"%i",POS_POWER_75_) ;
				break;
			case POS_POWER_100_ :
				sprintf(tmp,"%i",POS_POWER_100_) ;
				break;
			case NEG_POWER_5_ :
				sprintf(tmp,"%i",NEG_POWER_5_) ;
				break;
			case NEG_POWER_10_ :
				sprintf(tmp,"%i",NEG_POWER_10_) ;
				break;
			case NEG_POWER_20_ :
				sprintf(tmp,"%i",NEG_POWER_20_) ;
				break;
			case NEG_POWER_25_ :
				sprintf(tmp,"%i",NEG_POWER_25_) ;
				break;
			case NEG_POWER_50_ :
				sprintf(tmp,"%i",NEG_POWER_50_) ;
				break;
			case NEG_POWER_75_ :
				sprintf(tmp,"%i",NEG_POWER_75_) ;
				break;
			case NEG_POWER_100_ :
				sprintf(tmp,"%i",NEG_POWER_100_) ;
				break;
            case NULL_POWER_VALUE :
                sprintf(tmp,"%i",NULL_POWER_VALUE) ;
                break ;
		}
		return strdup(tmp) ;
	 }

/**
 * @overview : placer la puissance au bon endroit dans la payload
 * @arg : cmd_type  la commande demandée; power_percent_type le pourcentage demandé ;
 * @return : char* la chaine correspondante (sans le header)
 * **/
char* placer_puissance(cmd_type cmd, power_percent_type percent){

	char tmp[200];
	
	switch(cmd){
        case CMD_GAUCHE :
            sprintf(tmp,"%s%s%s",",1,",convert_power(percent) ,",0,0,0\r") ;
            break;
        case CMD_DROITE :
            sprintf(tmp,"%s%s%s",",1,", convert_power(percent) , ",0,0,0\r") ;
            break;
		case CMD_AVANT :
			sprintf(tmp,"%s%s%s",",1,0,", convert_power(percent) , ",0,0\r") ;
			break ;
		case CMD_ARRIERE :
			sprintf(tmp,"%s%s%s",",1,0,", convert_power(percent) , ",0,0\r") ;
			break;
		case CMD_HAUT :
			sprintf(tmp,"%s%s%s",",1,0,0,", convert_power(percent) , ",0\r") ;
			break;
		case CMD_BAS :
			sprintf(tmp,"%s%s%s",",1,0,0,", convert_power(percent) , ",0\r") ;
			break;
		case CMD_ROTATION_GAUCHE :
			sprintf(tmp,"%s%s%s",",1,0,0,0,", convert_power(percent) , "\r") ;
			break;
		case CMD_ROTATION_DROITE :
			sprintf(tmp,"%s%s%s",",1,0,0,0,", convert_power(percent), "\r") ;
			break;
        case CMD_DECOLLAGE :
            sprintf(tmp,"%s",",290718208\r") ;
            break;
        case CMD_ATTERISSAGE :
            sprintf(tmp,"%s",",290717696\r") ;
            break;
        case CMD_ARRET_URGENCE :
            sprintf(tmp,"%s",",290717952\r") ;
            break;
        case CMD_ANTI_ARRET_URGENCE :
            sprintf(tmp,"%s",",290717696\r") ;
            break;
        case CMD_CLOSE_CONNEC :
            sprintf(tmp,"%s",COMMANDE_CLOSE_CONNEC) ;
            printf("closing connection\n") ;
            break ;
	}
	return strdup(tmp) ;
}


/**
 * @overview : créer la payload a envoyer en respectant les normes AR Drone
 * @arg : cmd_type commande voulue (Cf. com.h "CMD_*")
 * @return : char* pointeur vers le string créé
 * @TODO : factoriser le switch case par une sous fonction
 * **/

char* make(cmd_type trg,power_percent_type percent){

        size_t taille = TAILLE_COMMANDE ;
        char commande_result[taille];
        memset(commande_result,0,100);
        commande_result[99]='\0';
        //size_t taille ;
		switch(trg){
			case CMD_DECOLLAGE :
                //taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
                //commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,H_AT_REF) ;
				strcat(commande_result,numSequence) ;
                strcat(commande_result,placer_puissance(CMD_DECOLLAGE,percent)) ;
				break ;
			case CMD_ATTERISSAGE :
                //taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_ATTERISSAGE) ;
                //commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,H_AT_REF) ;
				strcat(commande_result,numSequence) ;
                strcat(commande_result,placer_puissance(CMD_ATTERISSAGE,percent)) ;
				break ;
			case CMD_ARRET_URGENCE :
                //taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_ARRET_URGENCE) ;
                //commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,H_AT_REF) ;
				strcat(commande_result,numSequence) ;
                strcat(commande_result,placer_puissance(CMD_ARRET_URGENCE,percent)) ;
				break ;
			case CMD_ANTI_ARRET_URGENCE :
                //taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_ANTI_ARRET_URGENCE) ;
                //commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,H_AT_REF) ;
				strcat(commande_result,numSequence) ;
                strcat(commande_result,placer_puissance(CMD_ANTI_ARRET_URGENCE,percent)) ;
				break ;
			case CMD_AVANT :
                //taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_AVANT) ;
                //commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,placer_puissance(CMD_AVANT,percent)) ;
				break ;
			case CMD_ARRIERE :
                //taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_ARRIERE) ;
                //commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,placer_puissance(CMD_ARRIERE,percent)) ;
				break ;
			case CMD_GAUCHE :
                //taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_GAUCHE) ;
                //commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,numSequence) ;				
				strcat(commande_result,placer_puissance(CMD_GAUCHE,percent)) ;
				break ;
			case CMD_DROITE :
                //taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DROITE) ;
                //commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,placer_puissance(CMD_DROITE,percent)) ;
				break ;
			case CMD_HAUT :
                //taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_HAUT) ;
                //commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,placer_puissance(CMD_HAUT,percent)) ;
				break ;
			case CMD_BAS :
                //taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_BAS) ;
                //commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,placer_puissance(CMD_BAS,percent)) ;
				break ;
			case CMD_ROTATION_GAUCHE :
                //taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_ROTATION_GAUCHE) ;
                //commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,placer_puissance(CMD_ROTATION_GAUCHE,percent)) ;
				break ;
			case CMD_ROTATION_DROITE :
                //taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_ROTATION_DROITE) ;
                //commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,placer_puissance(CMD_ROTATION_DROITE,percent)) ;
				break ;
             case CMD_CLOSE_CONNEC :
                strcat(commande_result,placer_puissance(CMD_CLOSE_CONNEC,NULL_POWER_VALUE));
                printf("making close commande") ;
                break ;
		}
        //result=strdup(commande_result) ;
	   	PRINT_LOG("Command created : %s", commande_result)
        //free(commande_result) ;
		EXIT_FCT() ;
        return strdup(commande_result) ;
	}


/**
 *@overview : envoie un paquet udp
 *aucun controle n'est fait sur le comportement de l'automate d'envoie
 *@arg : char* commande voulue, size_t size of the payload (strlenght)
 *@return : int state
 * **/
int send_cmd(cmd_type cmd,power_percent_type percent) {

	ENTER_FCT()
	// on réalise le payload à l'aide de la commande demandée
        char*  payload = NULL ;
	// on ouvre ou ferme la connection en fonction de ce qui est demandé
        if(cmd != CMD_CLOSE_CONNEC && connectionOpen==0){
			printf("init socket : %d\n",initialize_socket());
			connectionOpen=1 ;
		}
        if(cmd == CMD_CLOSE_CONNEC && connectionOpen==1){ //DONE : Quel message envoyer au drone pour cesser la connection? : num de séquence remis à zéro
			if(close_socket()==0){
				connectionOpen=0 ;
                numSeq = 0 ;
                printf("socket closed\n");
                EXIT_FCT()
				return 0 ;
			}
			EXIT_FCT()
            printf("socket not closed properly\n");
			return -1; // EXIT 1
		}
        inc_num_sequence();
        payload = make(cmd,percent);
        if(payload!=NULL && strlen(payload)<1024){
			PRINT_LOG("Command to send : %s", payload)
            printf("CMD envoyée? : %s : ",payload) ;
			if(send_message(payload)==0){
				connectionOpen=1 ;
                printf("true \n") ;
                if(payload!=NULL)
                    free(payload);
				EXIT_FCT()
				return 0 ;
			}
            printf("false \n") ;
        }
        if(payload!=NULL)
            free(payload);
        EXIT_FCT()
        return -1; // EXIT 3
}

/** factorisation des fonctions gestion de vol
 * @arg : commande de vol
 * @return : status
 * */
int manage_cmd(cmd_type cmd, power_percent_type percent,int times){
	ENTER_FCT()
	cmd_type generalCommande = cmd ;
	int nb_envoie = 1;
	int return_val = 0 ;
	int cpt = 0 ;

	if(cmd==CMD_CLOSE_CONNEC){
        numSeq = 0 ;
        return send_cmd(cmd,percent) ;
	}
	if(times!=0)
		 nb_envoie+=times-1;
		 
	for(cpt=0;cpt<NB_ESSAI_UDP*nb_envoie;cpt++){
		return_val += send_cmd(generalCommande,percent) ;
        DELAY(31) ;
	}
    EXIT_FCT()
	return return_val ;
}

/**
 * decoller
 * @arg : void
 * @return : status 0 = OK
 * **/
 
int taking_off_AT(){
	ENTER_FCT()
	return manage_cmd(CMD_DECOLLAGE,NULL_POWER_VALUE,0) ;
}
/**
 * atterir
 * @arg : void
 * @return : status 0 = OK
 * **/
 int landing_AT(){
    ENTER_FCT()
	return manage_cmd(CMD_ATTERISSAGE,NULL_POWER_VALUE,0) ;

}
/**
 * monter
 * @arg : times <=> on envoie le commande pendant times*35ms
 * @return : status 0 = OK
 * **/

 int rising_AT(int times,power_percent_type percent) {
 	ENTER_FCT()
	return manage_cmd(CMD_HAUT,percent,times) ;
}

/**
 * descendre
 * @arg : times <=> on envoie le commande pendant times*35ms
 * @return : status 0 = OK
 * **/
int go_down_AT(int times,power_percent_type percent){
    ENTER_FCT()
	return manage_cmd(CMD_BAS,percent,times) ;
}

/**
 * tourner, faire une rotation
 * @arg : times <=> on envoie le commande pendant times*35ms
 * @return : status 0 = OK
 * **/
int turn_AT_Right(int times,power_percent_type percent) {
	ENTER_FCT()
	return manage_cmd(CMD_ROTATION_DROITE,percent,times) ;
}
int turn_AT_Left(int times,power_percent_type percent){
	ENTER_FCT()
	return manage_cmd(CMD_ROTATION_GAUCHE,percent,times) ;
}

/**
 * avancer / reculer
 * @arg : times <=> on envoie le commande pendant times*35ms
 * @return : status 0 = OK
 * **/
int go_forward_AT(int times,power_percent_type percent){
	ENTER_FCT()
	return manage_cmd(CMD_AVANT,percent,times) ;
}
int go_back_AT(int times,power_percent_type percent){
	ENTER_FCT()
	return manage_cmd(CMD_ARRIERE,percent,times) ;
}

/**
 * aller a gauche/droite (translation)
 * @arg : times <=> on envoie le commande pendant times*35ms
 * @return : status 0 = OK
 * **/
int translate_right(int times,power_percent_type percent){
	ENTER_FCT()
	return manage_cmd(CMD_DROITE,percent,times) ;
}
int translate_left(int times,power_percent_type percent){
	ENTER_FCT()
	return manage_cmd(CMD_GAUCHE,percent,times) ;
}

/**
 * arret d'urgence
 * @arg : void
 * @return : status 0 = OK
 * **/
 int emergency_stop(){
	ENTER_FCT()
	return manage_cmd(CMD_ARRET_URGENCE,NULL_POWER_VALUE,0) ;
}
/**
 * arret d'urgence
 * @arg : void
 * @return : status 0 = OK
 * **/
 int no_emergency_stop(){
	ENTER_FCT()
	return manage_cmd(CMD_ANTI_ARRET_URGENCE,NULL_POWER_VALUE,0) ;
}

/**
 * close connection
 * @arg : void
 * @return : status 0 = OK
 * **/
 int close_connect(){
	ENTER_FCT()
	return manage_cmd(CMD_CLOSE_CONNEC,NULL_POWER_VALUE,0) ;
}
	 

