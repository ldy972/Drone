#ifndef _LIFT_LAND_H_
#define _LIFT_LAND_H_

/**User Define**/
#define GAZ 0
#define PHI 0
#define THETA 0
#define YAW 0.5

#include <ardrone_api.h>
#include <ardrone_tool/UI/ardrone_input.h>
#include <VP_Os/vp_os_types.h>
#include <unistd.h>
#include <stdio.h>
#include <Navdata/navdata.h>

PROTO_THREAD_ROUTINE( lift_land , nomParams );


/**Bit 0 : when Bit0=0 the drone will enter the hovering mode, i.e. try to stay on top of a fixed
point on the ground, else it will follow the commands set as parameters.
• Bit 1 : when Bit1=1 AND CONTROL:control_level configuration Bit1=1, the new Com-
bined Yaw mode is activated. This mode includes a complex hybridation of the phi pa-
rameter to generate complete turns (phi+yaw).
* **/

/**Flag enabling the use of progressive commands and the new Com-
bined Yaw control mode
Left/right angle ∈ [−1.0; +1.0]
)
Front/back angle ∈ [−1.0; +1.0]
Vertical speed ∈ [−1.0; +1.0]
Angular speed ∈ [−1.0; +1.0]**/
typedef enum {
	HOVERING_CONT=0b10,
	HOVERING =0b00,
	NO_HOVERING_CONT=0b11,
	NO_HOVERING=0b01	
	} FLAG_Type ;
typedef enum{
	ZERO=0 ,
	FULL_POS = 1 ,
	FULL_NEG = -1 
	} POWER_Type ;

//int go = 0 ;
//extern const navdata_demo_t *User_Nav_Data;

#endif // _LIFT_LAND_H_
