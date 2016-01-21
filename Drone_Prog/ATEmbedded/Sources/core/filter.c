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

//Takes a file containing float at each line
float get_mean_from_file(const char* filename)
{
    float sum = 0.0 ;
    int values_count = 1 ;
    
    char** endptr=NULL ;
    FILE *file;
    file = fopen(filename, "r");
    
    if(file!=NULL)
    {    
         char line[20] ;

         while(fgets(line,sizeof(line),file))
         {  
            suppress_return(file,line);
            //printf("string number %d : %s\n", values_count,line);
            sum += strtod(line,endptr);
            values_count++ ;
         }
        
         fclose(file); 
    }
    values_count-- ;
    
    printf("Nb of values to average : %d\n",values_count);

    if(values_count > 0)
    {
        return (sum/values_count) ; 
    }
    else
    { 
        return 0.0 ;
    }
    
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
trajectory_measure_t get_max_measure(trajectory_measure_t *measure)
{
    //WRITE CORRELATION CODE
}



//Returning the heading and power according to the max power
//Full rotation retrieving the power each 10 degrees
//Correlation
trajectory_measure_t get_measure(){
	trajectory_measure_t my_measure[36];
	float init_cap;
	int i=0;

	//Every 10 degrees: calculate the signal power and the cap
	my_measure[i].cap = retrieve_heading();
	my_measure[i].power = get_power();
	init_cap = get_power();
	
	turn_right(75,10.0);
	while(retrieve_heading()<init_cap+360){
		
		printf("Cap:%f\n", my_measure[i].cap);
		printf("Power:%f\n", my_measure[i].power);
		
		i++;
		my_measure[i].cap = retrieve_heading();
		my_measure[i].power = get_power();
	
		turn_right(75,10.0);
	}

	//Correlation
        // /!\
	return my_measure[1]; //get_max_measure(&my_measure);
}

/*int main()
{
  return 0 ; 
} */  



