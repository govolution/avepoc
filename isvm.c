// source: https://www.pelock.com/articles/anti-reverse-engineering-malware-vs-antivirus-software
// some changes needed ;)

#include <windows.h>
#include <stdio.h>

BOOL IsVM()
{
    HKEY hKey;
    int i;
    char szBuffer[1024];
    char *szProducts[] = { "VMWARE", "VBOX", "VIRTUAL", "VMware" };
//printf("count of szProducts: %d\n",_countof(szProducts));
    DWORD dwSize = sizeof(szBuffer) - 1;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\Disk\\Enum", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        RegQueryValueEx(hKey, "0", NULL, NULL, (unsigned char *)szBuffer, &dwSize );
        printf("szbuffer test 1: %s\n",szBuffer);
        //if (RegQueryValueEx(hKey, "0", NULL, NULL, (unsigned char *)szBuffer, &dwSize ) == ERROR_SUCCESS)
        {
            printf("count of szProducts: %d\n",_countof(szProducts));
            for (i = 0; i < _countof(szProducts); i++)
            {
                if (strstr(szBuffer, szProducts[i]))
                {
                    RegCloseKey(hKey);
                    return TRUE;
                }
                printf("search %d\n",i);
		printf("szBuffer: %s, szPRoductsi:%s\n",szBuffer,szProducts[i]);
        }
    }

    RegCloseKey(hKey);
}

  return FALSE;
}

int main(void)
{
	printf("isvm: %d\n",IsVM());
}

