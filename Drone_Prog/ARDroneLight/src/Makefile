all : test_udp

clean :
	rm *.o test_udp

test_udp : udp_sender.o test_udp.o 
	gcc -Wall udp_sender.o test_udp.o -o $@

%.o : %.c $(wildcard *.h)
	gcc -Wall -DEMBED -c $<

