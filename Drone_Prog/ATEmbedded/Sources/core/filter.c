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

//Returning the max power from a table
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
	
    return max_measure;
}

//Returning the min power from a table
trajectory_measure_t get_min_measure(trajectory_measure_t * measure, int size)
{
    trajectory_measure_t min_measure;
    min_measure.power = FLT_MAX;

    int i;
    for (i = 0; i < size; i++){
        if (min_measure.power > measure[i].power) {
            min_measure = measure[i];
        }
    }
	
    return min_measure;
}





//Rotation 10° by 10°, construction of the (heading,power) array  
//Correlation
trajectory_measure_t get_measure(){
	
	int size = 50 ;
	trajectory_measure_t * measure_array;
	trajectory_measure_t result ;
	measure_array = malloc(sizeof(trajectory_measure_t)*size) ;
        int i = 0, j = 0, k = 0 ;
	float init_cap = 0.0 ;

	for(j=0;j<size;j++)
	{
		measure_array[i].cap = 0.0 ;
		measure_array[i].power = 0.0 ;
	}

	float prev_heading;
	
	init_cap = get_heading() ;
	printf("\nCap_init:%f\n", init_cap);		
	measure_array[i].cap = get_heading();
	measure_array[i].power=measure();
	printf("Cap : %f\n", measure_array[i].cap);
	printf("Power : %f\n", measure_array[i].power);
	rotate_right_mag(75,10.0);
	prev_heading = init_cap;
	while(get_heading() > prev_heading){
		prev_heading = get_heading();
		i++;
		measure_array[i].cap = get_heading() ;
		measure_array[i].power = measure() ;	
		printf("Cap : %f\n", measure_array[i].cap) ;
		printf("Power : %f\n", measure_array[i].power) ;
		rotate_right_mag(75,10.0);
		sleep(1.5);
	}
	

	/*while(get_heading() < init_cap){
		i++;
		measure_array[i].cap = get_heading() ;
		measure_array[i].power = measure() ;	
		printf("Cap : %f\n", measure_array[i].cap) ;
		printf("Power : %f\n", measure_array[i].power) ;
		rotate_right_mag(75,10.0);
		sleep(1.5);
	}*/

	//printf("\nOut of while, rotation done\n") ;
/*
	for(k=0;k<i;k++)
	{
		printf("cap : %f ; mesure : %f\n",measure_array[k].cap,measure_array[k].power) ;
	}*/
	printf("==================================================\n") ;
	for(k=0;k<=i;k++)
	{
		printf("%-8.3lf ",measure_array[k].power) ;
	}
	printf("\n") ;
	for(k=0;k<=i;k++)
		{
			printf("%-8.3lf ",measure_array[k].cap) ;
		}
	printf("\n\n");
	
	result = get_max_measure(measure_array,i) ;
	printf("max power found : %f at %f\n", result.power,result.cap) ;
	free(measure_array) ;	
	return(result);
	
	//correlation
}


trajectory_measure_t get_measure_presentation(){
	
	int size = 50 ;
	trajectory_measure_t * measure_array;
	trajectory_measure_t result ;
	measure_array = malloc(sizeof(trajectory_measure_t)*size) ;
        int i = 0, j = 0, k = 0 ;
	float init_cap = 0.0 ;

	for(j=0;j<size;j++)
	{
		measure_array[i].cap = 0.0 ;
		measure_array[i].power = 0.0 ;
	}

	float prev_heading;
	
	init_cap = get_heading() ;
	printf("\nCap_init:%f\n", init_cap);		
	measure_array[i].cap = get_heading();
	measure_array[i].power=measure();
	printf("Cap : %f\n", measure_array[i].cap);
	printf("Power : %f\n", measure_array[i].power);
	getchar() ;
	//rotate_right_mag(75,10.0);	
	prev_heading = init_cap;
	while(get_heading() > prev_heading){
		prev_heading = get_heading();
		i++;
		getchar() ;
		measure_array[i].cap = get_heading() ;
		measure_array[i].power = measure() ;	
		printf("Cap : %f\n", measure_array[i].cap) ;
		printf("Power : %f\n", measure_array[i].power) ;
		//rotate_right_mag(75,10.0);
		//sleep(1.5);
	}
	

//	printf("\nOut of while, rotation done\n") ;
	
	 
	printf("==================================================\n") ;
	for(k=0;k<=i;k++)
	{
		printf("%-8.3lf ",measure_array[k].power) ;
	}
	printf("\n") ;
	for(k=0;k<=i;k++)
		{
			printf("%-8.3lf ",measure_array[k].cap) ;
		}
	printf("\n\n");
	
	result = get_max_measure(measure_array,i) ;
	printf("max power found : %f at %f\n", result.power,result.cap) ;
	free(measure_array) ;	
	return(result);
	
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



