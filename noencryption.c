/*
Filename: noencryption.c
Author: Daniel Sauder
Website: http://govolution.wordpress.com
License http://creativecommons.org/licenses/by-sa/3.0/
Purpose: Demonstrate a simple shell binder
*/

#include <stdio.h>

unsigned char buf[] = 
"your shellcode here";

int main(int argc, char **argv)
{
	int (*funct)();
	funct = (int (*)()) buf;
	(int)(*funct)();
}
