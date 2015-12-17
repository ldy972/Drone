#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "../core/com_AT.h"
#include "../core/navdata.h"
#include "../core/shared.h"


#define SEC_DELAY(x) {sleep(x);}

int main(void)
{
    printf("Init navdata socket\n");
    init_navdata_reception();
    //initialize_connection_with_drone();

    printf("Get navdata\n");
    int go_on = 1;

    while (go_on < 50) {
        reload_watchdog();
        //receive data 
		printf("Navdata reset\n") ;
        update_navdata();
		printf("Nav data received\n") ;
        // printf("decode navdata_struct %d bytes\n",sizeof(navdata_struct));
        printf("navdata_demo:\n");
        printf("\t%13d:%s\n",   navdata_struct->navdata_option.ctrl_state,             "Control State");
        printf("\t%13d:%s\n",   navdata_struct->navdata_option.vbat_flying_percentage, "battery");
        printf("\t%13.3f:%s\n", navdata_struct->navdata_option.theta,                  "pitch angle");
        printf("\t%13.3f:%s\n", navdata_struct->navdata_option.phi,                    "roll  angle");
        printf("\t%13.3f:%s\n", navdata_struct->navdata_option.psi,                    "yaw   angle");
        printf("\t%13d:%s\n",   navdata_struct->navdata_option.altitude,               "altitude");
        printf("\t%13.3f:%s\n", navdata_struct->navdata_option.vx,                     "estimated vx");
        printf("\t%13.3f:%s\n", navdata_struct->navdata_option.vy,                     "estimated vy");
        printf("\t%13.3f:%s\n", navdata_struct->navdata_option.vz,                     "estimated vz");
        printf("\n\n");
        go_on ++;
        usleep(500000);       
    }

    printf("Close navdata socket\n");
    close_navdata_connection();

    return 0;
}
