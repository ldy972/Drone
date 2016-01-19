
CROSS_COMPILE = arm-linux-gnueabi-gcc
ARCH = arm

ifeq ($(EMBED),embed)
    	CROSS_COMPILE = arm-linux-gnueabi-gcc
	EXEC = transcriptIQ.elf
	CFLAGS = -W -Wall -march=armv7-a -lm
else 
	CROSS_COMPILE = gcc
	EXEC = transcriptIQ
	CFLAGS = -W -Wall -lm
endif

all : $(EXEC)

$(EXEC) : 
	$(CROSS_COMPILE) transcriptIQ.c -o $(EXEC) $(CFLAGS)
	
#cleanning part
clean :
	rm -rf ./*.o
	
mrproper : clean
	rm -rf ./*.*~
	rm -rf ./$(EXEC)
	
