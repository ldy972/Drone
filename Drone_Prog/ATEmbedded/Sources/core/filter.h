#include <string.h>
#include <stdio.h>
#include <stdlib.h>

float get_mean_from_file(const char* filename);
static void vider_buffer(FILE *f);
static void suppress_return(FILE *f, char* chain);
void generate_acquisition_file(char * filename_bin, char * filename_txt, char * frequency, char * sampling);

