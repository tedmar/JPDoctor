/*
 *  tcomms.c
 *      Simple serial communications
 */

/*
 *  set_interface_attribs:
 *      Cheange speed of open terminal file
 */

void set_interface_attribs(int fd, int speed);

/*
 *  read_line:
 *      reads a line terminated by new line
 *      from terminal open file descriptor 'fd'
 *      in buffer 'buf' of total size 'size'
 */

int read_line( int fd, char buf[], int size );


