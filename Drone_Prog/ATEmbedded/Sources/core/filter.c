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

void generate_acquisition_file(char * filename_bin, char * filename_txt, char * frequency, char * sampling)
{
    char command_transcript[70]="" ;
    char command_rtl[70]="" ; 

    strcat(command_rtl,"./rtl_sdr ") ;
    strcat(command_rtl,filename_bin);
    strcat(command_rtl," -s ") ;
    strcat(command_rtl,sampling) ;
    strcat(command_rtl," -f ") ;
    strcat(command_rtl,frequency) ;
 
    strcat(command_transcript,"./transcriptIQ.elf ");
    strcat(command_transcript, filename_bin) ;
    strcat(command_transcript, " ");
    strcat(command_transcript, filename_txt);

    printf("command_transcript : %s\n",command_transcript);
    printf("command_rtl : %s\n",command_rtl);
    
    system (command_rtl) ; 
    system ("^C") ;   
    system (command_transcript) ;
}

/*int main()
{
  return 0 ; 
} */  



