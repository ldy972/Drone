#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shared.h"


float get_power_from_file(const char* filename);
static void vider_buffer(FILE *f);
static void suppress_return(FILE *f, char* chain);
void generate_acquisition_file(char * filename_csv);
trajectory_measure_t get_max_measure(trajectory_measure_t *measure);
trajectory_measure_t get_measure();
