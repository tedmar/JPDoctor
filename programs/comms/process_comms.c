/*
 *  process_comms.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tcomms.h"
#include "process_comms.h"

#define forever for(;;)

enum
{
    STOPPED, STARTED,
    NUM_STATES
};

static int state = STOPPED;


/*
 *  process_comms
 *      Do whatever process needed over
 *      terminal opened under file descriptor 'fd'
 */

void
process_comms( int fd )
{
    char buf[81], saved[81];

    forever
    {
//        memset(buf,0,sizeof(buf));
        read_line(fd,buf,sizeof(buf));
        strcpy(saved,buf);
        switch(state)
        {
            case STOPPED:
                if( strstr(saved, "Start") != NULL )
                {
                    state = STARTED;
                    printf( "%s", saved );
                }
                break;
            case STARTED:
                printf( "%s", saved );
                if( strstr(saved, "Stop") != NULL )
                    state = STOPPED;
                break;
            default:
                break;
        }
    }
}



