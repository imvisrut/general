
/**************************************************

file: demo_rx.c
purpose: simple demo that receives characters from
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_rx.c rs232.c -Wall -Wextra -o2 -o test_rx

**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"



int main()
{
  int i, n,
      cport_nr=0,        /* /dev/ttyS0 (COM1 on windows) */
      bdrate=9600;       /* 9600 baud */

  unsigned char buf[1];

  char mode[]={'8','N','1',0};


  if(RS232_OpenComport(cport_nr, bdrate, mode))
  {
    printf("Can not open comport\n");
    return(0);
  }

  int fd = open("test.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);

  while(1)
  {
    n = RS232_PollComport(cport_nr, buf, 1);

    if(n > 0)
    {
      buf[n] = 0;   /* always put a "null" at the end of a string! */

      if(buf[0] == '^') {
        write(fd, EOF, 1);
        close(fd);
        return 0;
      }

      // printf("received %i bytes: %s\n", n, (char *)buf);
      printf("%s", (char *)buf);
      
      // fputs((char *)buf , fptr);
      write(fd, (char *)buf, strlen((char *)buf));
      // fprintf(fptr, (char *)buf);
    }
  }

  close(fd);

  return 0;
}

