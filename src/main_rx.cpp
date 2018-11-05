// MAIN_RX.CPP

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
#include <queue>


#define PI 3.141592

int main(void)
{
	int fd_parani2;
	struct termios newtio_rx;
    struct pollfd poll_events; // event struct ( interrupt )
    int poll_state;

    int num_byte;
    char buf[1024];

    printf("This is PARANI2 (RX) node.\n");
	fd_parani2 = open("/dev/PARANI2", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd_parani2 == -1)
		printf("Error - no serial port /dev/PARANI2 is opened! Check the serial device.\n");
	else
		printf("/dev/PARANI2 is opened.\n");
	memset(&newtio_rx, 0, sizeof(newtio_rx));
	newtio_rx.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	newtio_rx.c_oflag = 0;
	newtio_rx.c_lflag = 0;
	newtio_rx.c_cc[VTIME] = 0;
	newtio_rx.c_cc[VMIN] = 1;

	tcflush(fd_parani2, TCIFLUSH);
	tcsetattr(fd_parani2, TCSANOW, &newtio_rx);

    // poll preparation
    poll_events.fd = fd_parani2;
    poll_events.events = POLLIN | POLLERR; // if received or if there is error.
    poll_events.revents = 0;

	// read
    int cnt = 0;
    std::queue<char> data_queue;
    while(1)
    {

        // polling stage. (when some data is received.)
        poll_state = poll( //poll() call. event check.
            (struct pollfd*)&poll_events, // event registration
            1, // the number of pollfd which we want to check.
            500); // time out [ms]
        if(poll_state > 0)
        {
            if(poll_events.revents & POLLIN) // event is receiving data.
            {
                num_byte = read(fd_parani2, buf, 1024);
                printf("Data received - cnt : %d, %d %s\n", cnt, num_byte, buf);
                
                for(int i=0;i < num_byte; i++)
                {   data_queue.push(buf[i]);
                    buf[i] ='\0'; // initialize all buffer.
                }
                num_byte = 0;
                cnt++;

                printf("Queue size : %d\n",data_queue.size());
            }
            if(poll_events.revents & POLLERR) // event is error ? 
            {
                printf("ERROR - There is communication error. program exit.\n");
                break;
            }
        }

        if(data_queue.size() > 10)
        {
            for(int i = 0; i < data_queue.size(); i++)
            {
                if(data_queue.front()!='@')
                {
                    data_queue.pop();
                    printf("pop\n");
                }
            }
        }
        usleep(1000*10);
       // read(fd_parani2, "forum", 5);
    }

	close(fd_parani2);
	return 0;
}