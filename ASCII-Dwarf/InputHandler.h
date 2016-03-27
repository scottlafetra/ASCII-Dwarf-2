#pragma once

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;


class EventReturn
{
public:
	int type; //0-keyboard, 1-mouse, 2-buffersizevent

	EventReturn();

	KEY_EVENT_RECORD* keyRecord;
	MOUSE_EVENT_RECORD* mouseRecord;
	pair<int,int> bufferRecord;
};

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	static InputHandler * GetHandler();
	vector<EventReturn> GetEvent();
	pair<int, int> GetScreenDimensions();
	void SafeClear();
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

