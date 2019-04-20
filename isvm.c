// source: https://www.pelock.com/articles/anti-reverse-engineering-malware-vs-antivirus-software
// some changes needed ;)
// tested with vmware workstation & virtualbox

#include <windows.h>
#include <stdio.h>

BOOL IsVM()
{
    HKEY hKey;
    int i;
    char szBuffer[1024];
    char *szProducts[] = { "VMWARE", "VBOX", "VIRTUAL", "VMware" };
    DWORD dwSize = sizeof(szBuffer) - 1;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\Disk\\Enum", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        RegQueryValueEx(hKey, "0", NULL, NULL, (unsigned char *)szBuffer, &dwSize );
        for (i = 0; i < _countof(szProducts); i++)
        {
            if (strstr(szBuffer, szProducts[i]))
            {
                RegCloseKey(hKey);
                return TRUE;
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

