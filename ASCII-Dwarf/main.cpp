#include "ASCII-Graphics.h"
#include "InputHandler.h"
#include "windows.h"
#include <iostream>
#include <vector>

using namespace std;


int main() {
	//80 x 25

	std::cout.sync_with_stdio(false);

	ASCII::Graphic screenBuffer(80, 23);
	ASCII::JumpingGraphic cursor(5, 5, { 
		{ '#', '#' , '#' , '#' , '#' },
		{ '#', 'O' , ' ' , 'O' , '#' },
		{ '#', ' ' , 'A' , ' ' , '#' },
		{ '#', '>' , '-' , '<' , '#' },
		{ '#', '#' , '#' , '#' , '#' }
	});

	ASCII::JumpingGraphic dwarf(1, 1, { {'@'} });

	//screenBuffer.draw(cursor);
	screenBuffer.draw(dwarf);
	screenBuffer.flush();

	while (true)
	{
		InputHandler* input = InputHandler::GetHandler();
		vector<EventReturn> events = input->GetEvent();

		for (EventReturn e : events)
		{
			if (e.type == 0)
			{
				KEY_EVENT_RECORD* ker = e.keyRecord;
				if (ker->bKeyDown)
				{

					switch (ker->wVirtualKeyCode)
					{
					case 'W':
						dwarf.jump(0, -1, screenBuffer);
						break;

					case 'A':
						dwarf.jump(-1, 0, screenBuffer);
						break;

					case 'S':
						dwarf.jump(0, 1, screenBuffer);
						break;

					case 'D':
						dwarf.jump(1, 0, screenBuffer);
						break;
					}

					input->SafeClear();
					screenBuffer.flush();
					//cout << dwarf.getPosition().y << endl;

				}
				
			}
			else if (e.type == 1)
			{
				MOUSE_EVENT_RECORD* mer = e.mouseRecord;
				//cout << mer->dwMousePosition.X << "|" << mer->dwMousePosition.Y << endl;
				//cursor.jumpTo(mer->dwMousePosition.X - 2, mer->dwMousePosition.Y - 2, screenBuffer);
				//input->SafeClear();
				//screenBuffer.flush();
			}
			else if (e.type == 2)
			{
				pair<int,int> csbi = e.bufferRecord;
				//cout << csbi->srWindow.Right << " | " << csbi->dwSize.Y << endl;
				screenBuffer = ASCII::Graphic(csbi.first, csbi.second - 1);
			}
		}
	}

	system("pause");
	return 0;
}