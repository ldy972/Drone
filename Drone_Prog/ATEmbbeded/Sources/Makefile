all : com

com : com.o udp_sender.o
	gcc -w -Wall -o com com.o udp_sender.o

com.o : com.c com.h
	gcc -W -Wall -o com.o -c com.c
	
udp_sender.o : udp_sender.c udp_sender.h
	gcc -W -Wall -o udp_sender.o -c udp_sender.c

clean :
	rm -rf *.o
