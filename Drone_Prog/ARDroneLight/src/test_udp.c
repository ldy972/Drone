#include <stdio.h>
#include <unistd.h>

#include "udp_sender.h"


int main ()
{
    printf("Testing UDP_sender for IP adress: %s and port: %d\n", IP_ADRESS, UDP_PORT);

    printf("Opening socket\n");
    initialize_socket();
    printf("Socket opened\n");
    int nb_messages = 50;
    int i = 0;

    printf("Sending %d messages\n", nb_messages);
    char * mess = "Test";

    for (i = 0; i < nb_messages; i++)
    {
        send_message(mess);
        printf("Sending message %d\n", i);
    }

    printf("Closing socket\n");
    close_socket();
    printf("Socket closed\n");

    return 0;
}
