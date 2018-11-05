// MAIN_TX.CPP

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
	struct termios newtio_tx;
    printf("This is PARANI1 (TX) node.\n");
	fd_parani1 = open("/dev/PARANI1", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd_parani1 == -1)
		printf("Error - no serial port /dev/PARANI1 is opened! Check the serial device.\n");
	else
		printf("/dev/PARANI1 is opened.\n");
	memset(&newtio_tx, 0, sizeof(newtio_tx));
	newtio_tx.c_cflag = B115200;
	newtio_tx.c_cflag |= CS8;
	newtio_tx.c_cflag |= CLOCAL | CREAD;
	newtio_tx.c_iflag = 0; // no parity
	newtio_tx.c_oflag = 0;
	newtio_tx.c_lflag = 0;
	newtio_tx.c_cc[VTIME] = 0;
	newtio_tx.c_cc[VMIN] = 1;

	tcflush(fd_parani1, TCIFLUSH);
	tcsetattr(fd_parani1, TCSANOW, &newtio_tx);

    // write
    int cnt=0;
    clock_t start, finish;
    write(fd_parani1, "%%%%%%%%%%%%%%", 14);
    while(1)
    {
        start = clock();
        write(fd_parani1, "@@Changhyeon##", 14);
        printf("write tx cnt : %d\n",cnt);
        cnt++;
        usleep(1000*100);
        finish = clock();
	    double duration = (double)(finish - start) / 1000.0;
	    printf("TX : %f [ms]\n", duration+1000);
    }

	close(fd_parani1);
	return 0;
}
