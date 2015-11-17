#include "udp_sender.h"

int socket_id;
struct sockaddr_in addr_dest;


int initialize_socket()
{
    // Initalize socket
    if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("Echec de création du socket\n");
        return 1;
    }

    // Initialize destination adress structure
    bzero(&addr_dest, sizeof(struct sockaddr_in));
    addr_dest.sin_family = AF_INET;
    addr_dest.sin_port = htons(UDP_PORT);
    addr_dest.sin_addr.s_addr = inet_addr(IP_ADRESS);

    return 0;
}


int send_message(char* message)
{



}

 
int close_socket()
{


}
