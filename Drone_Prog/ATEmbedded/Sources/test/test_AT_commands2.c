#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "../core/com_AT.h"
#include "../core/udp_sender.h"
#include "../core/debug.h"


#define SEC_DELAY(x) {sleep(x);}

int main(void)
{
    int power_percent = 50 ;
    int times = 25 ;

    printf("Init connection\n");
    initialize_connection_with_drone();

    SEC_DELAY(2);

    printf("Décollage\n");
    take_off(); 
    printf("Dodo Décollage\n");
    DELAY(6000000)
    printf("Up Up !!\n");
    up(power_percent, times);
    DELAY(4000000);
    printf("Rotation droite ! \n");
    rotate_right(power_percent, 8 * times);
    printf("Dodo\n");
    DELAY(4000000)
    printf("Rotation gauche !\n");
    rotate_left(power_percent,times) ;
    //printf("En avant Gingamp !\n");
    //forward(power_percent,times) ;
    printf("Dodo\n");
    DELAY(2000000)
    printf("Retour sur le plancher des vaches\n");
    land();
    printf("Fini\n");

    return 0;
}


