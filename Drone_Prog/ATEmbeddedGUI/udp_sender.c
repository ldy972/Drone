#include "udp_sender.h"

static int socket_id;
static struct sockaddr_in addr_dest;


int initialize_socket()
{
    // Initalize socket
    if((socket_id = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        fprintf(stderr, "Echec de création du socket\n");
        return 1;
    }

    // Initialize destination adress structure
    bzero(&addr_dest, sizeof(struct sockaddr_in));
    addr_dest.sin_family = AF_INET;
    addr_dest.sin_port = htons(UDP_PORT);
    if (inet_aton(IP_ADRESS, &addr_dest.sin_addr) == 0)
    {
        fprintf(stderr, "Echec d'association de l'adresse IP au socket\n");
        return 2;
    }

    return 0;
}


int send_message(char* message)
{
    //Envoi du message, avec affichage si envoi réussi
    if (sendto(socket_id, message, strlen(message), 0, (struct sockaddr *) &addr_dest, (socklen_t) sizeof(struct sockaddr_in)) == -1)
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
