#ifndef UDP_SENDER_H
#define UDP_SENDER_H

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>


#ifdef EMBED
#define IP_ADRESS   "127.0.0.1"     // localhost for embedded version
#else 
#define IP_ADRESS   "192.168.1.1"   // static IP of the drone for non embedded
#endif
#define UDP_COMMANDS_PORT   5556
#define UDP_NAVDATA_PORT    5554
#define MAX_BUF_LEN 1024

// Open a socket on port 5556 to send messages to the drone
int initialize_sockets();

// Send the message to the defined IP adress on port 5556
int send_message(char* message);

// Send the message to the defined IP adress on port 5554
int send_navdata(char* message);

// Close the socket
int close_sockets();

#endif //UDP_SENDER_H
