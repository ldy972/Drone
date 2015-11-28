#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "com.h"
#include "udp_sender.h"
#include "debug.h"


#define SEC_DELAY(x) {sleep(x);}

int main(void)
{
	power_percent_type power_percent = POS_POWER_50_ ;
	int times = 50 ;

    printf("Init navdata\n");
    initialize_connection_with_drone();

    SEC_DELAY(2);

    printf("Décollage\n");
	taking_off_AT(); 
    printf("Dodo Décollage\n");
	SEC_DELAY(6)
    printf("Up, up, and away !\n");
	rising_AT(times,power_percent);
    printf("Dodo Montée\n");
	/*SEC_DELAY(2)
    printf("A droite toute !\n");
	turn_AT_Right(times,power_percent) ;
    printf("Dodo Droite\n");
	SEC_DELAY(2)*/
    printf("Retour sur le plancher des vaches\n");
	landing_AT();
    printf("Fini\n");

    return 0;
}


