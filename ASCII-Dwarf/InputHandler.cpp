#include "InputHandler.h"

EventReturn::EventReturn()
{

}

InputHandler * InputHandler::instance = nullptr;

InputHandler::InputHandler()
{
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");
}

InputHandler::~InputHandler()
{

}

void InputHandler::SafeClear()
{
	system("cls");
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");
}

vector<EventReturn> InputHandler::GetEvent()
{

	// Wait for the events. 
	if (!ReadConsoleInput(
		hStdin,      // input buffer handle 
		irInBuf,     // buffer to read into 
		128,         // size of read buffer 
		&cNumRead)) // number of records read 
		ErrorExit("ReadConsoleInput");

	

	vector<EventReturn>  returnMe(cNumRead);

	// Dispatch the events to the appropriate handler. 
	for (int i = 0; i < cNumRead; i++)
	{
		switch (irInBuf[i].EventType)
		{
		case KEY_EVENT: // keyboard input 
			returnMe[i].type = 0;
			returnMe[i].keyRecord = &irInBuf[i].Event.KeyEvent;
			break;

		case MOUSE_EVENT: // mouse input 
			returnMe[i].type = 1;
			returnMe[i].mouseRecord = &irInBuf[i].Event.MouseEvent;
			break;

		case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
			returnMe[i].type = 2;
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			returnMe[i].bufferRecord = { csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom -csbi.srWindow.Top  +1 };
			break;

		case FOCUS_EVENT:  // disregard focus events 

		case MENU_EVENT:   //  right click event
			returnMe[i].type = -1;
			break;

		default:
			ErrorExit("Unknown event type");
			break;
		}
	}

	return returnMe;
}

InputHandler * InputHandler::GetHandler()
{
	if (InputHandler::instance == nullptr)
	{
		InputHandler::instance = new InputHandler();
	}

	return InputHandler::instance;
}

void InputHandler::ErrorExit(LPSTR lpszMessage)
{

}

void InputHandler::KeyEventProc(KEY_EVENT_RECORD ker)
{
	int keyCode = ker.wVirtualKeyCode;

	if (ker.bKeyDown) //Key Press Event
	{
		cout << keyCode << endl;
	}
	else // Key Release Event
	{
		cout << keyCode << endl;
	}
}

void InputHandler::MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	cout << ("Mouse event: ");

	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cout << ("left button press") << endl;
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			cout << ("right button press") << endl;
		}
		else
		{
			cout << ("button press") << endl;
		}
		break;
	case DOUBLE_CLICK:
		cout << ("double click") << endl;
		break;
	case MOUSE_HWHEELED:
		cout << ("horizontal mouse wheel") << endl;
		break;
	case MOUSE_MOVED:
		cout << ("mouse moved") << endl;
		cout << mer.dwMousePosition.X << "|" << mer.dwMousePosition.Y << endl;
		break;
	case MOUSE_WHEELED:
		cout << ("vertical mouse wheel") << endl;
		break;
	default:
		cout << ("unknown") << endl;
		break;
	}
}
