
/**************************************************

file: demo_tx.c
purpose: simple demo that transmits characters to
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_tx.c rs232.c -Wall -Wextra -o2 -o test_tx

**************************************************/

#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"



int main()
{
  
  int cport_nr=0,        /* /dev/ttyS0 (COM1 on windows) */
      bdrate=9600;       /* 9600 baud */

  char mode[]={'8','N','1',0};


  if(RS232_OpenComport(cport_nr, bdrate, mode))
  {
    printf("Can not open comport\n");

    return(0);
  }

  FILE *fptr = fopen("test.txt", "r");
  if(fptr == NULL) {
    printf("file could not be opened");
    exit(1);
  }

  char c = fgetc(fptr);
  while (c != EOF)
  {
    c = fgetc(fptr);
    RS232_SendByte(cport_nr, c);
  }

  RS232_cputs(cport_nr, "####");

  fclose(fptr);

  return(0);
}

