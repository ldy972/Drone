#Yann LABEL# futur makefile# v1 17/11/2015# obj : permettre une 
#compilation générique via une arborescence fixée# target : Cortex A8 
#(armv7)# compilateur : arm-linux-gnueabi-gcc#


ifdef EMBED
	CC = arm-linux-gnueabi-gcc
	CFLAGS = -march=armv7-a
	EXEC = inc howard_cc.elf
else
	CC = gcc 
	EXEC = inc howard
endif

CXXFLAGS = -W -Wall
LDFLAGS =

SRCS_DIR:= $(shell pwd)/Sources
OBJS_DIR:= $(shell pwd)/Build
LIB_DIR:= $(shell pwd)/Lib
SRC=$(wildcard  $(SRCS_DIR)/*.c)
OBJS= $(SRC:.c=.o)

#include part : si la compilation nécessite un makefile particulier, l'insérer dans son dossier Sources
ifdef EMBED
	CFLAGS+= -DEMBED
endif

-include $(wildcard $(LIB_DIR)/*)
#-include moving.sh

all : $(EXEC)
	
$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
$(inc):
	@(cd $(SRCS_DIR) && $(MAKE))
	@(cd $(LIB_DIR) && $(MAKE))
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o
	rm -rf ~.o
	rm -rf *.elf
	rm -rf ~.elf
	./moving.sh
	rm -rf $(OBJS_DIR)/*
	
mrproper: clean
	rm -rf $(EXEC)
