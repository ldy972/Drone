#include "filter.h"

//If a line is longer than the buffer defined in get_mean_from_file, it is reduced.
void vider_buffer(FILE *f)
{
    char c;
    while ((c=fgetc(f)) != '\n' && c != EOF);
}

//We get rid of the \n character in each line of the file
void suppress_return(FILE *f, char* chain)
{  
    char *p = strchr(chain, '\n');
    if (p)
    {
        *p = 0;
    }
    else 
    {
        vider_buffer(f);
    }    
}

float get_power_from_file(const char* filename)
{
    float power1=0.0, power2=0.0,power_target=-9999;
    FILE *file;
    file = fopen(filename, "r");
    int i = 0 ;
    if(file!=NULL)
    {    
	while(fscanf(file,"%*d-%*d-%*d, %*d:%*d:%*d, %*d, %*d, %*f, %*d, %f, %f",&power1,&power2)>0 && ++i<12){
			if(power1>power_target)
				power_target = power1 ;
			if(power2>power_target)
				power_target = power2 ;
		}
		fclose(file); 
    } else 
		printf("error openning file\n") ;
    return power_target ;
}

//Write <filename>.csv --> don't forget the .csv, no protections inside ! ;)
void generate_acquisition_file(char * filename_csv)
{
    char command_acq[70]="" ; 
    
    strcat(command_acq,"./rtl_power.elf -f 1.235G:1.245G:1M -g 50 -i 1 -1 ") ;
    strcat(command_acq,filename_csv) ;
    
   // printf("%s", command_acq) ;
    system (command_acq) ; 
}

//Returning the max power according to the correlation
trajectory_measure_t get_max_measure(trajectory_measure_t * measure, int size)
{
    trajectory_measure_t max_measure;
    max_measure.power = -FLT_MAX;

    int i;
    for (i = 0; i < size; i++){
        if (max_measure.power < measure[i].power) {
            max_measure = measure[i];
        }
    }

    free(measure) ;	
    return max_measure;
}

//Rotation 10° by 10°, construction of the (heading,power) array  
//Correlation
trajectory_measure_t * get_measure(){
	
	int size = 50 ;
	trajectory_measure_t * measure_array;
	measure_array = malloc(sizeof(trajectory_measure_t)*size) ;
        int i = 0, j = 0 ;
	float init_cap = 0.0 ;

	for(j=0;j<size;j++)
	{
		measure_array[i].cap = 0.0 ;
		measure_array[i].power = 0.0 ;
	}

	
	init_cap = get_heading() ;
		
	do
	{	

		measure_array[i].cap = get_heading() ;
		measure_array[i].power = measure() ;	
		printf("Cap : %f\n", measure_array[i].cap) ;
		printf("Power : %f\n", measure_array[i].power) ;
		
		i++ ;
	
		rotate_right_mag(75,10.0) ;
		
	}
	while(get_heading() < init_cap + 360.0) ;

	return measure_array ; 
	
	//correlation
}


//creates the file and the max from it
float measure()
{  
    generate_acquisition_file("acquisition.csv") ;
    return(get_power_from_file("acquisition.csv")) ; 
}

/*int main()
{
  return 0 ; 
} */  



