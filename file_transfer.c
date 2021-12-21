
/**************************************************

file: demo_tx.c
purpose: simple demo that transmits characters to
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_tx.c rs232.c -Wall -Wextra -o2 -o test_tx

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
  int i=0,
      cport_nr=0,        /* /dev/ttyS0 (COM1 on windows) */
      bdrate=9600;       /* 9600 baud */

  char mode[]={'8','N','1',0};


  if(RS232_OpenComport(cport_nr, bdrate, mode))
  {
    printf("Can not open comport\n");

    return(0);
  }

  while(1)
  {
    FILE *file = fopen("demo.txt", "r");
    if(file == NULL) {
      printf("file not opened!");
      return 1;
    }
    char text[500];
    fscanf(file, "%[^\n]s", text);
    int m = 0;
    for(m = 0; m < strlen(text); m++)
    {
      RS232_SendByte(cport_nr, text[m]);
    }
    fclose(file);

#ifdef _WIN32
    Sleep(1000);
#else
    usleep(1000000);
#endif

    i++;

    i %= 2;
  }

  return(0);
}

