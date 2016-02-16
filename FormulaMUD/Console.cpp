#include "Pch.h"

#include "Console.h"

#include <Windows.h>


void Console::Init () {
	::FlushConsoleInputBuffer(::GetStdHandle(STD_INPUT_HANDLE));
}


bool Console::ReadLine (std::string * buffer) {
	DWORD handleWait = ::WaitForSingleObject(::GetStdHandle(STD_INPUT_HANDLE), 0);
	if (handleWait != WAIT_OBJECT_0)
		return false;

	DWORD numRead = 0;
	std::vector<char> rawbuf(256, 0);
	::ReadConsoleA(::GetStdHandle(STD_INPUT_HANDLE), &rawbuf[0], DWORD(rawbuf.size()), &numRead, NULL);

	if (!numRead)
		return false;

	*buffer = std::string(rawbuf.begin(), rawbuf.begin() + numRead);
	return true;
}

