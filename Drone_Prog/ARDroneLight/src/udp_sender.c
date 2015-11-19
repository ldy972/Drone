#include "udp_sender.h"

int socket_id;
struct sockaddr_in addr_dest;


int initialize_socket()
{
    // Initalize socket
    if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        fprintf(stderr, "Echec de création du socket\n");
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
    //Envoi du message, avec affichage si envoi réussi
    if (sendto(socket_id, message, strlen(message), 0, &addr_dest, sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "Erreur d'envoi de la commande %s", message);
        return 1;
    }

    return 0;
}

 
int close_socket()
{
    if(close(socket_id) == -1)
    {
        fprintf(stderr, "Erreur lors de la fermeture du socket");
        return 1;
    } 

    return 0;
}
