#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "comm_def.h"
#include "tcomms.h"
#include "process_comms.h"

static char *portname;
static int baud;

static void
eval_args( int argc, char *argv[] )
{
    portname = TERMINAL_DEFAULT;
    baud = BAUD_DEFAULT;

    if( argc > 1 )
    {
        if( argv[1][0] == '-' && argv[1][1] == 'h' )
        {
            printf( "%s port baud\n", argv[0] );
            exit( EXIT_SUCCESS );
        }
        portname = argv[1];
    }

    if( argc > 2 )
        baud = atoi(argv[2]);

    fprintf( stderr, "Executing: %s %s %d\n", argv[0], portname, baud );
}

int
main(int argc, char *argv[])
{
    int fd;

    eval_args( argc, argv ); 

    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        fprintf( stderr, "Error opening %s: %s\n", portname, strerror(errno));
        return EXIT_FAILURE;
    }

    set_interface_attribs(fd, B115200);

    process_comms(fd);

    return EXIT_SUCCESS;
}




