/* from: killprocess but exits */

#include <iostream>
#include <string>
#include <tchar.h>
#include <process.h>
#include <windows.h>
#include <tlhelp32.h>

using namespace std;

BOOL GetProcessList();
BOOL TerminateBlacklistedProcess(DWORD dwProcessId, UINT uExitCode);

int main( void )
{
  GetProcessList( );
  return 0;
}

BOOL GetProcessList( )
{
  printf("GetProcessList\n");
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  DWORD dwPriorityClass;

  //Blacklisted processes
  LPSTR ProcessName[] = { "ida.Exe",
                          "ProcMon.exe",
                          "OLLYDBG.EXE",
                          "Wireshark.exe",
                          "iexplore.exe"
                            };

  // Take a snapshot of processes
  hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
  if( hProcessSnap == INVALID_HANDLE_VALUE )
  {
    printf("exit\n");
    return( FALSE );
  }

  pe32.dwSize = sizeof( PROCESSENTRY32 );

  if( !Process32First( hProcessSnap, &pe32 ) )
  {
    CloseHandle( hProcessSnap );
    return( FALSE );
  }

  do
  {
    string str(pe32.szExeFile);

    for (int i = 0; i < (sizeof(ProcessName) / sizeof(LPSTR)); i++)
    {
        //cout << "[*] processus exists: " << (ProcessName[i]) << endl;
         if(str == ProcessName[i])
         {
             cout << "[*] processus found, exit: " << (ProcessName[i]) << endl;
             return (TRUE);
         }
    }
  } while( Process32Next( hProcessSnap, &pe32 ) );

  CloseHandle( hProcessSnap );
  return( TRUE );
}
