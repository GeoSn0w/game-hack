// Find game module
// By GeoSn0w (@FCE365), 2019

#include <Windows.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h>
#include <tchar.h>

using namespace std;

DWORD getBaseModuleAtPath(TCHAR *moduleName, DWORD PID);

// Global variables
DWORD PID;
DWORD baseAddr;
DWORD moduleAddr;

// Gets the name of the module to find and the PID of the running game.
// It will create a snapshot and iterate through until it finds the appropriate module. 
// Useful because the static pointers you find with tools like Cheat Engine are often relative to a specific module which has its own address.

DWORD getBaseModuleAtPath(TCHAR *moduleName, DWORD PID) {
	HANDLE Snappy = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
	MODULEENTRY32 gameModule = { 0 };
	gameModule.dwSize = sizeof(MODULEENTRY32);
	// Eat the snapshot and find the game module.
	if (Module32First(Snappy, &gameModule)) {
		do {
			if (_tcscmp(gameModule.szModule, moduleName) == 0) { // A fancy string compare.
				baseAddr = (DWORD)gameModule.modBaseAddr;
        printf("Want beef? 0x%x", baseAddr);
				break;
			}
		} while (Module32Next(Snappy, &gameModule)); // Continue until we find what we need. A game may have multiple modules.
	}
	CloseHandle(Snappy); // Always close the handles when you don't use them, otherwise you create mem issues with other processes that may wanna access the resource. 
	return baseAddr;
}
