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


/*int main()
{
  return 0 ; 
} */  



