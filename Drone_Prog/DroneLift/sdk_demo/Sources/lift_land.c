#include "lift_land.h"


// Corps du thread pour décolle et aterrir
DEFINE_THREAD_ROUTINE( lift_land, nomParams )
{
	int i = 0,j=0;
	float phi = PHI ;
	float theta = THETA;
	float gaz = GAZ;
	float yaw = YAW;
	FLAG_Type yaw_flag = NO_HOVERING;
	
	
  // Décollage
  // TODO Utiliser les données de navigation pour déterminer que le drone a bien décollé
	  for (i = 0; i < 100; i++) {
		//ardrone_tool_set_ui_pad_start(1);
		usleep(100000);
		
	  }

		//ardrone_at_set_navdata_all() ;
		for (i = 0; i < 50; i++){
			//printf("Access\n\n") ;
			if(User_Nav_Data!=NULL){
				/*printf("Control state : %i\n",User_Nav_Data->ctrl_state);
				printf("Battery level : %i mV\n",User_Nav_Data->vbat_flying_percentage);
				printf("Orientation   : [Theta] %4.3f  [Phi] %4.3f  [Psi] %4.3f\n",User_Nav_Data->theta,User_Nav_Data->phi,User_Nav_Data->psi);*/
				printf("Altitude vision      : %i\n",User_Nav_Data->altitude_vision);
				printf("Altitude vz 		 : %2.3f\n",User_Nav_Data->altitude_vz);
				printf("Altitude ref		 : %i\n",User_Nav_Data->altitude_ref) ;
				printf("Altitude raw		 : %i\n",User_Nav_Data->altitude_raw) ;
				printf("Obs alt				 : %2.3lf\n",User_Nav_Data->obs_alt) ;
				printf("Num seq        		 : %d\n",i);
				//printf("\033[8A");
			}
			usleep(50) ;
		}
//  printf("YOLO\n");

	usleep(50000) ;

  // Tentative de rotation
  // TODO A faire marcher
  /*for(i=0;i<50;i++){
	  yaw=0 ;
	  ardrone_at_set_progress_cmd(yaw_flag,phi,theta,gaz,yaw);
	  usleep(5000);

	  ardrone_at_set_progress_cmd(yaw_flag,phi,theta,gaz,yaw);
	  //if(ardrone_academy_navdata_takeoff()){
		  yaw=0.5 ;
		  //ardrone_at_set_progress_cmd(yaw_flag,phi,theta,gaz,yaw);
		  printf("Test Nav data take off !\n");
	  //}
		
	  usleep(100000);
	  //ardrone_at_set_progress_cmd(yaw_flag,phi,theta,gaz,yaw);
	}*/

  usleep(50000);
  for (i = 0; i < 10; i++) {
  // Aterrissage
  // TODO Utiliser les données de navigation pour déterminer que le drone a bien aterri
    //ardrone_tool_set_ui_pad_start(0);
    usleep(1000);
    printf("Land\n");
  }

  return C_OK;
}
