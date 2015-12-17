#include "udp_sender.h"


/******************************************************************************
 * Global variables declarations
 *****************************************************************************/

static int socket_id_commands;
static struct sockaddr_in addr_dest_commands;

static int socket_id_navdata;
static struct sockaddr_in addr_dest_navdata;
static struct sockaddr_in addr_src_navdata;


/******************************************************************************
 * Local functions protypes
 *****************************************************************************/

int initialize_target_socket(int * sock_id, struct sockaddr_in * addr_dest, int port);
int initialize_socket_source(int * sock_id, struct sockaddr_in * addr_src, int port);
int send_to_socket(char * message, int * sock_id, struct sockaddr_in * addr_dest);
int close_socket(int * sock_id);



/******************************************************************************
 * UDP Sender functions declaration
 *****************************************************************************/

// Initialize the specified socket and the destiation address
int initialize_target_socket(int * sock_id, struct sockaddr_in * addr_dest, int port)
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
        fprintf(stderr, "Echec d'association de l'adresse destination au socket\n");
        return 2;
    }

    return 0;
}


// Initialize the source address
int initialize_socket_source(int * sock_id, struct sockaddr_in * addr_src, int port)
{
    // Initialize source adress structure
    bzero(addr_src, sizeof(struct sockaddr_in));
    addr_src->sin_family = AF_INET;
    addr_src->sin_addr.s_addr = htonl(INADDR_ANY);
    addr_src->sin_port = htons(UDP_NAVDATA_DEST);

    if (bind(*sock_id, (struct sockaddr *) addr_src, sizeof(* addr_src)) != 0)
    {
        fprintf(stderr, "Echec d'association de l'adresse source au socket\n");
        return 1;
    }

    return 0;
}


int initialize_commands_socket()
{
    int result = 0;

    // Initialize socket for control commands
    result = initialize_target_socket(&socket_id_commands, &addr_dest_commands, UDP_COMMANDS_PORT);

    return result;
}


int initialize_navdata_socket()
{
    int result = 0;

    // Initialize socket for navdata
    result = initialize_target_socket(&socket_id_navdata, &addr_dest_navdata, UDP_NAVDATA_PORT);

    // If succeded, initialize source address for navdata
    if (result == 0) {
        result = initialize_socket_source(&socket_id_navdata, &addr_src_navdata, UDP_NAVDATA_DEST);
    }

    return result == 0 ? result : result + 2;
}


// Open a socket on port 5554 for navdata
int initialize_sockets()
{
    int result = 0;

    // Initialize socket for control commands
    result = initialize_commands_socket();
    
    // If succeded, initialize socket for navdata
    if (result == 0) {
        result = initialize_navdata_socket();
    }

    // 1 and 2 : error for first socket; 3 and 4 : error for second socket
    // 5 : error for navdata source port
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
    int result = send_message_no_delay(message);

    usleep(35000);

    return result;
}

int send_message_no_delay(char* message)
{
    int result = 0;

    result = send_to_socket(message, &socket_id_commands, &addr_dest_commands);

    return result;
}

int send_navdata(char* message)
{
    return send_to_socket(message, &socket_id_navdata, &addr_dest_navdata);
}


// Retrieve navdata
int recieve_navdata(int * navdata)
{
    socklen_t navdata_size = sizeof(addr_dest_navdata);
    int result = 0;

    result = recvfrom(socket_id_navdata, navdata, 1024 * sizeof(int), 0, (struct sockaddr *) &addr_dest_navdata, &navdata_size);
    if (result == 0) {
        fprintf(stderr, "Erreur de réception");
    }

    return result;
}



// Close the specified socket
int close_socket(int * sock_id)
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
    result = close_commands_socket();

    // Close navdata socket
    result += close_navdata_socket();

    return result;
}


// Close the commands socket
int close_commands_socket()
{
    int result;

    // Close control commands socket
    result = close_socket(&socket_id_commands);

    return result;
}


// Close the navdata socket
int close_navdata_socket()
{
    int result;

    // Close control commands socket
    result = close_socket(&socket_id_navdata);

    return result;
}

