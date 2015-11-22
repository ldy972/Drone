#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "com.h"
#include "udp_sender.h"
#include "debug.h"

int main(void)
{
    printf("Décollage\n");
	taking_off_AT(); 
    printf("Dodo Décollage\n");
	sleep(6);
    printf("Up, up, and away !\n");
	rising_AT(500);
    printf("Dodo Montée\n");
	sleep(2);
    printf("A droite toute !\n");
	turn_AT_Right(500) ;
    printf("Dodo Droite\n");
	sleep(2);
    printf("Retour sur le plancher des vaches\n");
	landing_AT();
    printf("Fini\n");

    return 0;
}


