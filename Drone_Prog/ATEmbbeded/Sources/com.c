#include "com.h"


/**
 * @overview : gestion du numéro de séquence
 * @arg :
 * @return :
 * */
 void inc_num_sequence(void){

		if(++(numSeq[0])>'9'){
			numSeq[0] = '0';
			strcat(numSequence,numSeq);
			if(++(numSequence[2])=='9'){
				numSequence[2]='0';
				if(++(numSequence[1])=='9'){
					numSequence[1]='0';
					if(++(numSequence[0])=='9'){
						numSequence[0]='0';
						maxSeqReach++ ;
					}
				}
			}
		}
	 }

	 
/**
 * @overview : créer la payload a envoyer en respectant les normes AR Drone
 * @arg : char* commande voulue (Cf. com.h "CMD_*")
 * @return : char* pointeur vers le string créé
 * @TODO : factoriser le switch case par une sous fonction
 * **/
char* make(cmd_type trg){

		char* commande_result = NULL ;
		size_t taille ;
		switch(trg){
			case CMD_DECOLLAGE :
				taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
				commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,H_AT_REF) ;
				strcat(commande_result,COMMANDE_AT_DECOLLAGE) ;
			case CMD_ATTERISSAGE :
				taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
				commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,H_AT_REF) ;
				strcat(commande_result,COMMANDE_AT_ATTERISSAGE) ;
			case CMD_ARRET_URGENCE :
				taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
				commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,H_AT_REF) ;
				strcat(commande_result,COMMANDE_AT_ARRET_URGENCE) ;
			case CMD_ANTI_ARRET_URGENCE :
				taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
				commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,H_AT_REF) ;
				strcat(commande_result,COMMANDE_AT_ANTI_ARRET_URGENCE) ;
			case CMD_AVANT :
				taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
				commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,COMMANDE_AT_AVANT) ;
			case CMD_ARRIERE :
				taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
				commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,COMMANDE_AT_ARRIERE) ;
			case CMD_GAUCHE :
				taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
				commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,COMMANDE_AT_GAUCHE) ;
			case CMD_DROITE :
				taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
				commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,COMMANDE_AT_DROITE) ;
			case CMD_HAUT :
				taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
				commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,COMMANDE_AT_HAUT) ;
			case CMD_BAS :
				taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
				commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,COMMANDE_AT_BAS) ;
			case CMD_ROTATION_GAUCHE :
				taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
				commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,COMMANDE_AT_ROTATION_GAUCHE) ;
			case CMD_ROTATION_DROITE :
				taille = strlen(numSequence) + strlen(H_AT_REF) + strlen(COMMANDE_AT_DECOLLAGE) ;
				commande_result = (char*)malloc(taille*sizeof(char)) ;
				strcat(commande_result,numSequence) ;
				strcat(commande_result,H_AT_PCMD) ;
				strcat(commande_result,COMMANDE_AT_ROTATION_DROITE) ;
			default: commande_result = strdup("") ;
		}
		return commande_result ;
	}
	


/**
 *@overview : envoie un paquet udp
 *aucun controle n'est fait sur le comportement de l'automate d'envoie
 *@arg : char* commande voulue, size_t size of the payload (strlenght)
 *@return : int state
 * **/
int send_cmd(cmd_type cmd) {


	// on réalise le payload à l'aide de la commande demandée
		char*  payload = make(cmd) ;
	// on ouvre ou ferme la connection en fonction de ce qui est demandé
		if(connectionOpen==0){
			initialize_socket();
			connectionOpen=1 ;
		}
		if(cmd == CMD_CLOSE_CONNEC){ //TODO : Quel message envoyer au drone pour cesser la connection?
			if(close_socket()==0){
				connectionOpen=0 ;
				return 0 ;
			}
			
			return -1; // EXIT 1
		}
		
	//on envoie notre message
		if(strlen(payload)<1024){

			if(send_message(payload)==0){
				inc_num_sequence();
				connectionOpen=0 ;
				return 0 ;
			}
			return -1; // EXIT 2
		}
		exit(-1) ;
	}

/** factorisation des fonctions gestion de vol
 * @arg : commande de vol
 * @return : status
 * */
int manage_cmd(cmd_type cmd, int times){
	cmd_type generalCommande = cmd ;
	int nb_envoie = 1;
	int return_val = 0 ;
	int cpt = 0 ;
	if(cmd==CMD_CLOSE_CONNEC){
		return send_cmd(generalCommande) ;
	}
	if(times!=0)
		 nb_envoie+=times-1;
		 
	for(cpt=0;cpt<NB_ESSAI_UDP*nb_envoie;cpt++){
		return_val += send_cmd(generalCommande) ;
		DELAY() ;
	}
	return return_val ;
}
/**
 * decoller
 * @arg : void
 * @return : status 0 = OK
 * **/
 
int taking_off_AT(){

	return manage_cmd(CMD_DECOLLAGE,0) ;
}
/**
 * atterir
 * @arg : void
 * @return : status 0 = OK
 * **/
 int landing_AT(){
	return manage_cmd(CMD_ATTERISSAGE,0) ;
}
/**
 * monter
 * @arg : times <=> on envoie le commande pendant times*35ms
 * @return : status 0 = OK
 * **/
 int rising_AT(int times) {
	return manage_cmd(CMD_HAUT,times) ;
}

/**
 * descendre
 * @arg : times <=> on envoie le commande pendant times*35ms
 * @return : status 0 = OK
 * **/
int go_down_AT(int times){
	return manage_cmd(CMD_BAS,times) ;
}

/**
 * tourner, faire une rotation
 * @arg : times <=> on envoie le commande pendant times*35ms
 * @return : status 0 = OK
 * **/
int turn_AT_Right(int times) {
	return manage_cmd(CMD_ROTATION_DROITE,times) ;
}
int turn_AT_Left(int times){
	return manage_cmd(CMD_ROTATION_GAUCHE,times) ;
}

/**
 * avancer / reculer
 * @arg : times <=> on envoie le commande pendant times*35ms
 * @return : status 0 = OK
 * **/
int go_forward_AT(int times){
	return manage_cmd(CMD_AVANT,times) ;
}
int go_back_AT(int times){
	return manage_cmd(CMD_ARRIERE,times) ;
}

/**
 * aller a gauche/droite (translation)
 * @arg : times <=> on envoie le commande pendant times*35ms
 * @return : status 0 = OK
 * **/
int translate_right(int times){
	return manage_cmd(CMD_DROITE,times) ;
}
int translate_left(int times){
	return manage_cmd(CMD_GAUCHE,times) ;
}

/**
 * arret d'urgence
 * @arg : void
 * @return : status 0 = OK
 * **/
 int emergency_stop(){
	return manage_cmd(CMD_ARRET_URGENCE,0) ;
}
/**
 * arret d'urgence
 * @arg : void
 * @return : status 0 = OK
 * **/
 int no_emergency_stop(){
	return manage_cmd(CMD_ANTI_ARRET_URGENCE,0) ;
}

/**
 * close connection
 * @arg : void
 * @return : status 0 = OK
 * **/
 int close_connect(){
	return manage_cmd(CMD_CLOSE_CONNEC,0) ;
}
	 


