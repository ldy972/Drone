#include "filter.h"

//Si une ligne dépasse la longueur max spécifiée dans get_max_from_file, on la raccourcit.
static void vider_buffer(FILE *f)
{
    char c;
    while ((c=fgetc(f)) != '\n' && c != EOF);
}

//On enleve le caractere de retour à la ligne recopié dans chaque ligne du fichier
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

float get_max_from_file(const char* filename)
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
            printf("string lu numero %d : %s\n", values_count,line);
            sum += strtod(line,endptr);
            values_count++ ;
         }
        
         fclose(file); 
    }
    values_count-- ;
    
    printf("Nb valeurs à moyenner : %d\n",values_count);

    if(values_count > 0)
    {
        return (sum/values_count) ; 
    }
    else
    { 
        return 0.0 ;
    }
    
}


//Returning the max power according to the correlation
trajectory_measure_t get_max_measure(trajectory_measure_t *measure){

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
	while(get_heading() < init_cap+360){
		
		printf("Cap:%f\n", my_measure[i].cap);
		printf("Power:%f\n", my_measure[i].power);
		
		i++;
		my_measure[i].cap = retrieve_heading();
		my_measure[i].power = get_power();
	
		turn_right(75,10.0);
	}

	//Correlation
	return get_max_measure(&my_measure);
}
