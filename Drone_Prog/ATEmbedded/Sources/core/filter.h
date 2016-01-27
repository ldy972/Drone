#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "shared.h"
#include "com_AT.h"


float get_power_from_file(const char* filename);
void vider_buffer(FILE *f);
void suppress_return(FILE *f, char* chain);
void generate_acquisition_file(char * filename_csv);
trajectory_measure_t get_max_measure(trajectory_measure_t *measure, int size);
trajectory_measure_t get_min_measure(trajectory_measure_t *measure, int size);
trajectory_measure_t get_measure();
trajectory_measure_t get_measure_presentation();
float measure() ;
