#include <unistd.h>
#include <stdlib.h>
#include "com.h"
#include "udp_sender.h"

int main(void)
{
	taking_off_AT(); 
	sleep(6);
	rising_AT(500);
	sleep(2);
	turn_AT_Right(500) ;
	sleep(2);
	landing_AT();

    return 0;
}


