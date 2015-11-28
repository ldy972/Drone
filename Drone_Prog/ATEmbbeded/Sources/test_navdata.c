#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "navdata.h"
#include "debug.h"


#define SEC_DELAY(x) {sleep(x);}

int main(void)
{
    printf("Init navdata socket\n");
    init_connection();

    printf("Get navdata\n");
    int go_on = 1;

    nav_data_type navdata;

    while (go_on < 25) {
        //receive data 
        memset( &navdata, '\0', sizeof(navdata)); 
        receive_nav_data(&navdata);
    
        // printf("decode navdata_struct %d bytes\n",sizeof(navdata_struct));
        printf("navdata_demo:\n");
        printf("\t%13d:%s\n",   navdata.nav_data.ctrl_state,             "Control State");
        printf("\t%13d:%s\n",   navdata.nav_data.vbat_flying_percentage, "battery");
        printf("\t%13.3f:%s\n", navdata.nav_data.theta,                  "pitch angle");
        printf("\t%13.3f:%s\n", navdata.nav_data.phi,                    "roll  angle");
        printf("\t%13.3f:%s\n", navdata.nav_data.psi,                    "yaw   angle");
        printf("\t%13d:%s\n",   navdata.nav_data.altitude,               "altitude");
        printf("\t%13.3f:%s\n", navdata.nav_data.vx,                     "estimated vx");
        printf("\t%13.3f:%s\n", navdata.nav_data.vy,                     "estimated vy");
        printf("\t%13.3f:%s\n", navdata.nav_data.vz,                     "estimated vz");
        printf("\n\n");
        go_on ++;
    }

    printf("Close navdata socket\n");
    close_connection();

    return 0;
}
