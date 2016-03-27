#pragma once

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	static InputHandler * GetHandler();
	void Run();
private:
	static InputHandler * instance;

	HANDLE hStdin;
	DWORD fdwSaveOldMode;
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];

	
	void ErrorExit(LPSTR);
	void KeyEventProc(KEY_EVENT_RECORD);
	void MouseEventProc(MOUSE_EVENT_RECORD);
	void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
};

