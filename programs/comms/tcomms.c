/*
 *  tcomms.c
 *      Simple serial communications
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "tcomms.h"

/*
 *  set_interface_attribs:
 *      Cheange speed of open terminal file
 */

void
set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0)
    {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        exit( EXIT_FAILURE );
    }
    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    if (tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        exit( EXIT_FAILURE );
    }
}

/*
 *  read_line:
 *      reads a line terminated by new line
 *      from terminal open file descriptor 'fd'
 *      in buffer 'buf' of total size 'size'
 */

int
read_line( int fd, char buf[], int size )
{
    int rdlen;

//    memset(buf,0,size);
    rdlen = read(fd,buf,size-1);
    if( rdlen < 0 )
    {
        fprintf( stderr, "Error reading comm: %s ... Aborting\n", strerror(errno) );
        exit(EXIT_FAILURE);
    }
    buf[rdlen] = '\0';
    return rdlen;
}



