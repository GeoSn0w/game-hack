// Find and open a process for R/W
// By GeoSn0w (@FCE365), 2019

#include <Windows.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h>
#include <tchar.h>

using namespace std;

// Global variables
HANDLE procH;
DWORD PID;

// You pass it the name of the game window and it will find the process, grab its PID, open a handle for R/W and return the handle.
// Has sanity checks. Will bail out if the process cannot be found, if the window cannot be found or if the handle cannot be created.
HANDLE openProcForRW(TCHAR* who) {
	HWND hwnd = FindWindowA(NULL, who);
	if (hwnd != NULL) {
		printf("[i] Found process: %s\n", who);
	}
	else {
		printf("[-] Could not find the process. Please start the game and try again!\n");
		Sleep(3000);
		exit(-1);
	}
	GetWindowThreadProcessId(hwnd, &PID);
	if (PID == NULL) {
		printf("[-] Could not find PID for thread!\n");
		Sleep(3000);
		exit(-1);
	}
	printf("[+] Got PID: %d\n", PID);
	procH = OpenProcess(PROCESS_ALL_ACCESS, false, PID); // Yeee
	if (procH == NULL) {
		printf("[-] Could not open the process at PID for ALL_ACCESS! Bailing out...\n");
		Sleep(3000);
		exit(-1);
	}
	printf("[+] Successfully opened process at ID %d for R/W!\n", PID);
	return procH;
}
