#include "udp_sender.h"

static int socket_id_commands;
static struct sockaddr_in addr_dest_commands;

static int socket_id_navdata;
static struct sockaddr_in addr_dest_navdata;


// Initialize the specified socket
int initialize_dest_socket(int * sock_id, struct sockaddr_in * addr_dest, int port)
{
    // Initalize commands socket
    if((*sock_id = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        fprintf(stderr, "Echec de création du socket\n");
        return 1;
    }

    // Initialize destination adress structure
    bzero(addr_dest, sizeof(struct sockaddr_in));
    addr_dest->sin_family = AF_INET;
    addr_dest->sin_port = htons(port);
    if (inet_aton(IP_ADRESS, &(addr_dest->sin_addr)) == 0)
    {
        fprintf(stderr, "Echec d'association de l'adresse IP au socket commandes\n");
        return 2;
    }

    return 0;
}


int initialize_sockets()
{
    int result = 0;

    // Initialize socket for control commands
    result = initialize_dest_socket(&socket_id_commands, &addr_dest_commands, UDP_COMMANDS_PORT);
    
    // If succeded, initialize socket for navdata
    if (result == 0) {
        result = initialize_dest_socket(&socket_id_navdata, &addr_dest_navdata, UDP_NAVDATA_PORT);
    }

    // 1 and 2 : error for first socket; 3 and 4 : error for second socket
    return result == 0 ? result : result + 2;
}


// Send the message to the specified socket
int send_to_socket(char * message, int * sock_id, struct sockaddr_in * addr_dest)
{
    //Envoi du message, avec affichage si envoi réussi
    if (sendto(* sock_id, message, strlen(message), 0, (struct sockaddr *) addr_dest, (socklen_t) sizeof(struct sockaddr_in)) == -1)
    {
        fprintf(stderr, "Erreur d'envoi de la commande %s", message);
        return 1;
    }

    return 0;
}


int send_message(char* message)
{
    return send_to_socket(message, &socket_id_commands, &addr_dest_commands);
}

int send_navdata(char* message)
{
    return send_to_socket(message, &socket_id_navdata, &addr_dest_navdata);
}


// Close the specified socket
int close_dest_socket(int * sock_id)
{
    if(close(*sock_id) == -1)
    {
        fprintf(stderr, "Erreur lors de la fermeture du socket");
        return 1;
    } 

    return 0;
}


int close_sockets()
{
    int result;

    // Close control commands socket
    result = close_dest_socket(&socket_id_commands);

    // Close navdata socket
    result += close_dest_socket(&socket_id_navdata);

    return result;
}
