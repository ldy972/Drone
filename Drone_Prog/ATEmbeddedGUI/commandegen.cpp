#include "commandegen.h"

CommandeGen::CommandeGen()
{
    m_status = 0 ;
}

int CommandeGen::get_status(){
    return m_status ;
}

/**************************************************************************************
 * Function with Negate
 * ************************************************************************************/
void CommandeGen::go_gauche(int times, int percent) {
    m_status = turn_AT_Left(times,negate(to_percent(percent))) ;
}

void CommandeGen::descendre(int times,int percent){
    m_status = go_down_AT(times,negate(to_percent(percent))) ;
}

void CommandeGen::avancer(int times,int percent){
    m_status = go_forward_AT(times,negate(to_percent(percent))) ;
}

void CommandeGen::trans_left(int times,int percent) {
    m_status = translate_left(times,negate(to_percent(percent))) ;
}

/**************************************************************************************
 * Function without Negate
 * ************************************************************************************/
void CommandeGen::taking_off() {
    m_status = taking_off_AT() ;
}

void CommandeGen::landing(){
    m_status = landing_AT() ;
}

void CommandeGen::monter(int times,int percent) {
    m_status = rising_AT(times,to_percent(percent)) ;
}
void CommandeGen::reculer(int times,int percent) {
    m_status = go_back_AT(times,to_percent(percent)) ;
}

void CommandeGen::trans_right(int times,int percent) {
    m_status = translate_right(times,to_percent(percent)) ;
}

void CommandeGen::go_droite(int times, int percent) {
    m_status = turn_AT_Right(times,to_percent(percent)) ;
}

void CommandeGen::emerg_stop(){
    m_status = emergency_stop() ;
}

void CommandeGen::no_emerg_stop(){
    m_status = no_emergency_stop();
}

void CommandeGen::close() {
    m_status = close_connect();
}

/**
 * @brief CommandeGen::to_percent
 * Convertit un int en power_percent_type positive
 * Pour les sens Gauche Avant ET Descendre utilier la fonction "negate"
 * @param p
 * @return
 */
power_percent_type CommandeGen::to_percent(int p){
    power_percent_type percent = POS_POWER_5_ ;

    if(p<=5 && p>=0){
        percent = POS_POWER_5_ ;
    }else if(p<=10){
        percent = POS_POWER_10_ ;
    }else if(p<=20){
        percent = POS_POWER_20_ ;
    }else if(p<=25){
        percent = POS_POWER_25_ ;
    }else if(p<=50){
        percent = POS_POWER_50_ ;
    }else if(p<=75){
        percent = POS_POWER_75_ ;
    }else if(p<=100){
        percent = POS_POWER_100_ ;
    }
    return percent ;
}

/**
 * @brief CommandeGen::negate for (gauche _ avant _ descendre)
 * Renvoie le négative du power_percent_type placé en argument
 * @param p
 * @return
 */
power_percent_type CommandeGen::negate(power_percent_type p){
    power_percent_type percent = p ;
    switch(p){
        case POS_POWER_5_ :
            percent = NEG_POWER_5_ ;
            break ;
        case POS_POWER_10_ :
            percent = NEG_POWER_10_ ;
            break ;
        case POS_POWER_20_ :
            percent = NEG_POWER_20_ ;
            break ;
        case POS_POWER_25_ :
            percent = NEG_POWER_25_ ;
            break ;
        case POS_POWER_50_ :
            percent = NEG_POWER_50_ ;
            break ;
        case POS_POWER_75_ :
            percent = NEG_POWER_75_ ;
            break ;
        case POS_POWER_100_ :
            percent = NEG_POWER_100_ ;
            break ;
        default : percent = p  ; break ;
    }

    return percent ;
}
