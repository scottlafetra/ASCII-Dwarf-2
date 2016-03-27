#include "ASCII-Graphics.h"
#include "Scenery.h"
#include "InputHandler.h"
#include "windows.h"
#include <iostream>
#include <vector>

using namespace std;

ASCII::Graphic objectsBuffer(0, 0);
ASCII::Graphic backgroundBuffer(0, 0);
ASCII::Graphic screenBuffer(0, 0);
vector<ASCII::Graphic*> toRender;

void rerender() {
	screenBuffer.draw(backgroundBuffer);
	screenBuffer.drawWithAlpha(objectsBuffer);

	InputHandler::GetHandler()->SafeClear();
	screenBuffer.flush();
}

void rerenderComplete() {
	objectsBuffer.clear();
	for (ASCII::Graphic* element : toRender) {
		objectsBuffer.drawWithAlpha(*element);
	}

	rerender();
}

int main() {
	//80 x 25

	std::cout.sync_with_stdio(false);
	
	pair<int, int> screeenDimensions = InputHandler::GetHandler()->GetScreenDimensions();

	screenBuffer = backgroundBuffer = objectsBuffer = ASCII::Graphic(screeenDimensions.first, screeenDimensions.second-1);

	ASCII::WalkingGraphic cursor(5, 5, { 
		{ '#', '#' , '#' , '#' , '#' },
		{ '#', 'O' , ' ' , 'O' , '#' },
		{ '#', ' ' , 'A' , ' ' , '#' },
		{ '#', '>' , '-' , '<' , '#' },
		{ '#', '#' , '#' , '#' , '#' }
	}, 7);

	ASCII::WalkingGraphic dwarf(1, 1, { {'@'} }, { {FOREGROUND_BLUE | FOREGROUND_RED} });
	dwarf.moveTo(5, 5);
	toRender.push_back(&dwarf);

	Room room(10, 10);
	room.moveTo(10, 10);
	toRender.push_back(&room);

	//screenBuffer.draw(cursor);
	rerenderComplete();

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
						dwarf.walk (0, -1, objectsBuffer);
						break;

					case 'A':
						dwarf.walk(-1, 0, objectsBuffer);
						break;

					case 'S':
						dwarf.walk(0, 1, objectsBuffer);
						break;

					case 'D':
						dwarf.walk(1, 0, objectsBuffer);
						break;
					}

					input->SafeClear();
					rerender();
					//cout << dwarf.getPosition().y << endl;

				}
				
			}
			else if (e.type == 1)
			{
				MOUSE_EVENT_RECORD* mer = e.mouseRecord;

				if (mer->dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					int dx = mer->dwMousePosition.X - dwarf.getPosition().x;
					dx = max(min(dx, 1), -1);

					int dy = mer->dwMousePosition.Y - dwarf.getPosition().y;
					dy = max(min(dy, 1), -1);

					dwarf.walk(dx, dy, objectsBuffer);
					rerender();
					cout << dx << "|" << dy;
				}

				//cout << mer->dwMousePosition.X << "|" << mer->dwMousePosition.Y << endl;
				//cursor.jumpTo(mer->dwMousePosition.X - 2, mer->dwMousePosition.Y - 2, screenBuffer);
				//input->SafeClear();
				//screenBuffer.flush();
			}
			else if (e.type == 2)
			{
				pair<int,int> csbi = e.bufferRecord;
				//cout << csbi->srWindow.Right << " | " << csbi->dwSize.Y << endl;
				screenBuffer = backgroundBuffer = objectsBuffer = ASCII::Graphic(csbi.first, csbi.second - 1);
			}
		}
	}

	system("pause");
	return 0;
}