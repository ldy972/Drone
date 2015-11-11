#include "lift_land.h"



DEFINE_THREAD_ROUTINE( lift_land, nomParams )
{
  int i = 0;

  for (i = 0; i < 10; i++) {
    ardrone_tool_set_ui_pad_start(1);
    usleep(1000);
  }

  printf("YOLO\n");

  //ardrone_at_set_progress_cmd(1,0.5,1,1,1);
  //usleep(5000000);
  ardrone_at_set_progress_cmd(TRUE,0.0,0.0,1.0,0);



  usleep(5000000);
	ardrone_at_set_progress_cmd(TRUE,0.0,0.0,0.0,1);
usleep(5000000);
  for (i = 0; i < 10; i++) {
    ardrone_tool_set_ui_pad_start(0);
    usleep(1000);
  }
}
