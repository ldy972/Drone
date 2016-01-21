#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shared.h"

float get_max_from_file(const char* filename);
static void vider_buffer(FILE *f);
static void suppress_return(FILE *f, char* chain);
trajectory_measure_t get_measure();
