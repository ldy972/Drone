#include <stdio.h>
#include <stdlib.h>

// rtlsdr-to-gqrx Copyright 2014 Paul Brewer KI6CQ
// License: CC BY-SA 3.0 or GNU GPL 3.0
// IQ file converter 
// from rtl_sdr recording format -- interleaved unsigned char
// to gqrx/gnuradio .cfile playback format -- complex64 

void closing_file(FILE *infile, FILE *outfile){
	fclose(infile) ;
	fclose(outfile) ;
}
void main(int argc, char *argv[])
{
	int byte1, byte2;  // int -- not unsigned char -- see fgetc man page
	float fc;
	FILE *infile,*outfile;
	const float scale_carre = 1.0/(128.0*128.0);
	const char *infilename = argv[1];
	const char *outfilename = argv[2];
	if (argc<3){
		printf("usage:  rtlsdr-to-gqrx infile outfile\n");
		exit(1);
	}
	printf("in= %s out= %s \n", infilename, outfilename);
	infile=fopen(infilename,"rb");
	outfile=fopen(outfilename,"wb");
	if ((infile==NULL) && (outfile==NULL)){
		printf("Error opening files\n");
		closing_file(infile,outfile);
		exit(-10);
	} else if (infile==NULL){
		fclose(outfile) ;
		printf("Error opening input file : %s\n",infilename);
		exit(-11);
	}else if (outfile==NULL){
		fclose(infile) ;
	  	printf("Error opening output file : %s\n",outfilename);
		exit(-11);
	}
	while ((byte1=fgetc(infile)) != EOF){
		if ((byte2=fgetc(infile)) == EOF){
			closing_file(infile,outfile) ;
			exit(0);
		}    
		fc = (float)((byte1-127)*(byte1-127)+(byte2-127)*(byte2-127))*scale_carre;
		fprintf(outfile,"%2.5f\n",fc) ;
	}
	closing_file(infile,outfile);
}
