#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/poll.h>

#include <sys/time.h>

#define PI 3.141592

int main(void)
{
	int fd_parani1;
	struct termios newtio_tx, newtio_rx;

	fd_parani1 = open("/dev/PARANI1", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd_parani1 == -1)
		printf("Error - no serial port /dev/PARANI1 is opened! Check the serial device.\n");
	else
		printf("/dev/PARANI1 is opened.\n");
	memset(&newtio_tx, 0, sizeof(newtio_tx));
	newtio_tx.c_cflag = B9600;
	newtio_tx.c_cflag |= CS8;
	newtio_tx.c_cflag |= CLOCAL | CREAD;
	newtio_tx.c_iflag = 0; // no parity
	newtio_tx.c_oflag = 0;
	newtio_tx.c_lflag = 0;
	newtio_tx.c_cc[VTIME] = 0;
	newtio_tx.c_cc[VMIN] = 1;

	int fd_parani2 = open("/dev/PARANI2", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if(fd_parani2 == -1 )
		printf("Error - no serial port /dev/PARANI2 is opened! Check the serial device.\n");
	else
		printf("/dev/PARANI2 is opened.\n");
	tcflush(fd_parani1, TCIFLUSH);
	tcsetattr(fd_parani1, TCSANOW, &newtio_tx);


	// read and write
	write(fd_parani1, "forum", 5);
	write(fd_parani1, "forum", 5);

	close(fd_parani1);
	close(fd_parani2);

	return 0;
}
