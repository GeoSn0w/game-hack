// Read / Write Primitives for game hacking on Windows.
// GeoSn0w 2019

#include <Windows.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h>
#include <tchar.h>

int WriteAnywhere64(int what, DWORD where);
ReadAnywhere64(DWORD where, int howMuch);

// Write primitive. This one accepts a value (an integer as it is assumed you wanna change health, ammo, etc.) and an address where to write.
int WriteAnywhere64(int what, DWORD where) {
	if (WriteProcessMemory(procH, (LPVOID)where, &what, sizeof(what),0)){
		return 0;
	}
	return -1;
}

// Read primitive. This one accepts an address as an argument. It will read at that address. 
// You set the size by passing an integer to the second argument.
int ReadAnywhere64(DWORD where, int howMuch) {
	DWORD rv;
	if (ReadProcessMemory(procH, (LPCVOID)where, &rv, howMuch, NULL)) {
		return rv;
	}
	return -1;
}

