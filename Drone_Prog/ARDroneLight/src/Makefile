all : test_udp

clean :
	rm *.o test_udp

test_udp : test_udp.o udp_sender.o
	gcc -Wall test_udp.o udp_sender.o -o $@

%.o : %.c %.h
	gcc -Wall -DEMBED -c $<

