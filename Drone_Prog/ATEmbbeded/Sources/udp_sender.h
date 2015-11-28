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

// Open both sockets
int initialize_sockets();

// Open a socket on port 5556 to send AT commands to the drone
int initialize_commands_socket();

// Open a socket on port 5554 for navdata
int initialize_navdata_socket();

// Send the message to the defined IP adress on port 5556
int send_message(char* message);

// Send the message to the defined IP adress on port 5554
int send_navdata(char* message);

// Close the sockets
int close_sockets();

// Close the commands socket
int close_commands_socket();

// Close the navdata socket
int close_navdata_socket();

#endif //UDP_SENDER_H
