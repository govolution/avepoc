/*
Author: Daniel Sauder
Filename: 64noencryption.c
Website: http://govolution.wordpress.com
License http://creativecommons.org/licenses/by-sa/3.0/
Purpose: shellcode binder 64bit
*/

#include <windows.h>
 
unsigned char sc[] = "shellcode";

typedef void (*FUNCPTR)(); 
 
int main(int argc, char **argv)
{
    FUNCPTR func;
    int len;
    DWORD oldProtect;

    len = sizeof(sc);

    if (0 == VirtualProtect(&sc, len, PAGE_EXECUTE_READWRITE, &oldProtect))
        return 1;    

    func = (FUNCPTR)sc;
    func();
 
    return 0;
}
