#include "lift_land.h"


// Corps du thread pour décolle et aterrir
DEFINE_THREAD_ROUTINE( lift_land, nomParams )
{
  int i = 0;

  // Décollage
  // TODO Utiliser les données de navigation pour déterminer que le drone a bien décollé
  for (i = 0; i < 10; i++) {
    ardrone_tool_set_ui_pad_start(1);
    usleep(1000);
    printf("On décolle\n");
  }

  printf("YOLO\n");
  usleep(10000000);

  // Tentative de rotation
  // TODO A faire marcher
//  for (i = 0; i < 100; i++) {
    ardrone_at_set_progress_cmd(TRUE,0,0,0.0,0.5);
    usleep(30000);
  //  printf("Up %d\n", i);
 // }
  ardrone_at_set_progress_cmd(0,0,0,0.0,0.0);
  printf("Stahp !\n");

  usleep(5000000);
  for (i = 0; i < 10; i++) {
  // Aterrissage
  // TODO Utiliser les données de navigation pour déterminer que le drone a bien aterri
    ardrone_tool_set_ui_pad_start(0);
    usleep(1000);
    printf("Land\n");
  }

  return C_OK;
}
