#include <stdio.h>
#include <unistd.h>

#include "../core/udp_sender.h"


int main ()
{
    printf("Testing UDP_sender for IP adress: %s and port: %d\n", IP_ADRESS, UDP_COMMANDS_PORT);

    printf("Opening socket\n");
    if (initialize_commands_socket() != 0)
    {
        printf("Fail INIT\n");
        return 1;
    }
    printf("Socket opened\n");
    int nb_messages = 10;
    int i = 0;

    printf("Sending %d messages\n", nb_messages);
    char * mess = "Test";

    for (i = 0; i < nb_messages; i++)
    {
        printf("Sending message %d: %s.\n", i, mess);
        if (send_message(mess) != 0)
        {
            printf("Fail INIT\n");
            return 2;
        }
        usleep(100000);
    }

    printf("Closing socket\n");
    if (close_commands_socket() != 0)
    {
        printf("Fail INIT\n");
        return 3;
    }
    printf("Socket closed\n");

    return 0;
}
