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
  }

  printf("YOLO\n");

  // Tentative de rotation
  // TODO A faire marcher
  ardrone_at_set_progress_cmd(0b11,0.5,0,0,1);
  usleep(5000000);
  ardrone_at_set_progress_cmd(0b00,0,0,0,0);

  usleep(5000000);
  for (i = 0; i < 10; i++) {
  // Aterrissage
  // TODO Utiliser les données de navigation pour déterminer que le drone a bien aterri
    ardrone_tool_set_ui_pad_start(0);
    usleep(1000);
  }
}
