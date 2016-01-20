#include <string.h>
#include <stdio.h>
#include <stdlib.h>

float get_max_from_file(const char* filename);
static void vider_buffer(FILE *f);
static void suppress_return(FILE *f, char* chain);

