#include "filter.h"

//If a line is longer than the buffer defined in get_mean_from_file, it is reduced.
static void vider_buffer(FILE *f)
{
    char c;
    while ((c=fgetc(f)) != '\n' && c != EOF);
}

//We get rid of the \n character in each line of the file
static void suppress_return(FILE *f, char* chain)
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

    return max_measure;
}


//Returning the heading and power according to the max power
//Full rotation retrieving the power each 10 degrees
//Correlation
trajectory_measure_t * get_measure(){
	trajectory_measure_t my_measure[50];
        int i = 0, j = 0 ;
	float init_cap; 
	for(j=0;j<50;j++)
	{
		my_measure[i].cap = 0.0 ;
		my_measure[i].power = 0.0 ;
	}

	//Every 10 degrees: calculate the signal power and the heading
//	my_measure[i].cap = get_heading();
//	my_measure[i].power = get_power(); //Recuperer la puissance 
	init_cap = get_heading();
       	
	rotate_right_mag(75,10.0);
	while(get_heading()<init_cap+360.0)
	{
	  
		my_measure[i].cap = get_heading();
		my_measure[i].power = measure();		
		printf("Cap : %f\n", my_measure[i].cap);
		printf("Power : %f\n", my_measure[i].power);
		
		i++;
	
		rotate_right_mag(75,10.0);
	}

	//Correlation
	return my_measure ; //get_max_measure(&my_measure);
}

float measure()
{  
    generate_acquisition_file("acquisition.csv") ;
    return(get_power_from_file("acquisition.csv")) ; 
}

/*int main()
{
  return 0 ; 
} */  



