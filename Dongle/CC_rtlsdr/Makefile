
CROSS_COMPILE = arm-linux-gnueabi-gcc
CFLAGS = -W -Wall -march=armv7-a -lrt -lpthread -lm
ARCH = arm
PKG_CONFIG_PATH=/home/yann/projets/CC_rtl/drone/lib/pkgconfig/

LIB_USB:=$(shell PKG_CONFIG_PATH=/home/yann/projets/CC_rtl/drone/lib/pkgconfig/ pkg-config --libs --cflags libusb-1.0)

all : init build_lib rtl_test.elf rtl_sdr.elf rtl_eeprom.elf rtl_adsb.elf rtl_fm.elf rtl_power.elf rtl_tcp.elf

test : init build_lib rtl_test.elf

sdr : init build_lib rtl_sdr.elf

eeprom : init build_lib rtl_eeprom.elf

adsb : init build_lib rtl_adsb.elf

fm : init build_lib rtl_fm.elf

power : init build_lib rtl_power.elf

tcp : init build_lib rtl_tcp.elf

#for export & init
init :
	$(wildcard export ARCH=$(ARCH))
	$(wildcard export CROSS_COMPILE=$(CROSS_COMPILE))

#building .o
build_lib : tuner_e4k.o tuner_fc0012.o tuner_fc0013.o tuner_fc2580.o tuner_r82xx.o librtlsdr.o convenience.o 

librtlsdr.o : librtlsdr.c rtl-sdr.h tuner_e4k.h tuner_fc0012.h tuner_fc0013.h tuner_fc2580.h tuner_r82xx.h rtlsdr_i2c.h
	$(CROSS_COMPILE) -o librtlsdr.o -c librtlsdr.c $(LIB_USB) $(CFLAGS)
	
tuner_e4k.o : tuner_e4k.c tuner_e4k.h reg_field.h rtlsdr_i2c.h
	$(CROSS_COMPILE) -o tuner_e4k.o -c tuner_e4k.c $(CFLAGS)
	
tuner_fc0012.o : tuner_fc0012.c tuner_fc0012.h rtlsdr_i2c.h
	$(CROSS_COMPILE) -o tuner_fc0012.o -c tuner_fc0012.c $(CFLAGS)
	
tuner_fc0013.o : tuner_fc0013.c tuner_fc0013.h rtlsdr_i2c.h
	$(CROSS_COMPILE) -o tuner_fc0013.o -c tuner_fc0013.c $(CFLAGS)
	
tuner_fc2580.o : tuner_fc2580.c tuner_fc2580.h rtlsdr_i2c.h
	$(CROSS_COMPILE) -o tuner_fc2580.o -c tuner_fc2580.c $(CFLAGS)
	
tuner_r82xx.o : tuner_r82xx.c tuner_r82xx.h rtlsdr_i2c.h
	$(CROSS_COMPILE) -o tuner_r82xx.o -c tuner_r82xx.c $(CFLAGS)

convenience.o : convenience.c convenience.h rtl-sdr.h rtl-sdr_export.h 
	$(CROSS_COMPILE) -o convenience.o -c convenience.c $(CFLAGS)
	
#specific .o for commande
rtl_test.o : rtl_test.c rtl-sdr.h convenience.h 
	$(CROSS_COMPILE) -o rtl_test.o -c rtl_test.c $(CFLAGS)
	
rtl_sdr.o :rtl_sdr.c rtl-sdr.h convenience.h 
	$(CROSS_COMPILE) -o rtl_sdr.o -c rtl_sdr.c $(CFLAGS)
	
rtl_eeprom.o : rtl_eeprom.c rtl-sdr.h
	$(CROSS_COMPILE) -o rtl_eeprom.o -c rtl_eeprom.c $(CFLAGS)

rtl_adsb.o : rtl_adsb.c rtl-sdr.h convenience.h 
	$(CROSS_COMPILE) -o rtl_adsb.o -c rtl_adsb.c $(CFLAGS)
	
rtl_fm.o :  rtl_fm.c rtl-sdr.h convenience.h 
	$(CROSS_COMPILE) -o rtl_fm.o -c rtl_fm.c $(CFLAGS)
	
rtl_power.o : rtl_power.c rtl-sdr.h convenience.h 
	$(CROSS_COMPILE) -o rtl_power.o -c rtl_power.c $(CFLAGS)

rtl_tcp.o : rtl_tcp.c rtl-sdr.h convenience.h 
	$(CROSS_COMPILE) -o rtl_tcp.o -c rtl_tcp.c $(CFLAGS)

#building .elf
rtl_test.elf : rtl_test.o
	$(CROSS_COMPILE) -o rtl_test.elf rtl_test.o librtlsdr.o convenience.o tuner_e4k.o tuner_fc0012.o tuner_fc0013.o tuner_fc2580.o tuner_r82xx.o $(LIB_USB) $(CFLAGS)

rtl_sdr.elf : rtl_sdr.o
	$(CROSS_COMPILE) -o rtl_sdr.elf rtl_sdr.o librtlsdr.o convenience.o tuner_e4k.o tuner_fc0012.o tuner_fc0013.o tuner_fc2580.o tuner_r82xx.o $(LIB_USB) $(CFLAGS)

rtl_eeprom.elf : rtl_eeprom.o
	$(CROSS_COMPILE) -o rtl_eeprom.elf rtl_eeprom.o librtlsdr.o convenience.o tuner_e4k.o tuner_fc0012.o tuner_fc0013.o tuner_fc2580.o tuner_r82xx.o $(LIB_USB) $(CFLAGS)

rtl_adsb.elf : rtl_adsb.o
	$(CROSS_COMPILE) -o rtl_adsb.elf rtl_adsb.o librtlsdr.o convenience.o tuner_e4k.o tuner_fc0012.o tuner_fc0013.o tuner_fc2580.o tuner_r82xx.o $(LIB_USB) $(CFLAGS)

rtl_fm.elf : rtl_fm.o
	$(CROSS_COMPILE) -o rtl_fm.elf rtl_fm.o librtlsdr.o convenience.o tuner_e4k.o tuner_fc0012.o tuner_fc0013.o tuner_fc2580.o tuner_r82xx.o $(LIB_USB) $(CFLAGS)

rtl_power.elf : rtl_power.o
	$(CROSS_COMPILE) -o rtl_power.elf rtl_power.o librtlsdr.o convenience.o tuner_e4k.o tuner_fc0012.o tuner_fc0013.o tuner_fc2580.o tuner_r82xx.o $(LIB_USB) $(CFLAGS)

rtl_tcp.elf : rtl_tcp.o
	$(CROSS_COMPILE) -o rtl_tcp.elf rtl_tcp.o librtlsdr.o convenience.o tuner_e4k.o tuner_fc0012.o tuner_fc0013.o tuner_fc2580.o tuner_r82xx.o $(LIB_USB) $(CFLAGS)

#cleanning part
clean :
	rm -rf ./*.o
	
mrproper : clean
	rm -rf ./*.*~
	rm -rf ./*.elf
