#include "Scenery.h"


Room::Room(const int& width, const int& height)
: Graphic(width, height) {
	//draw box
	//Top
	for (int i = 0; i < width; ++i) {
		charBuffer[0][i] = '#';
		chromaBuffer[0][i] = BACKGROUND_BLUE | 0b11110000;
	}
	//bottom
	for (int i = 0; i < width; ++i) {
		charBuffer[height - 1][i] = '#';
	}
	//Left
	for (int i = 0; i < width; ++i) {
		charBuffer[i][0] = '#';
	}
	//right
	for (int i = 0; i < width; ++i) {
		charBuffer[i][width - 1] = '#';
	}

	//cut holes in the box for doors
	//top
	charBuffer[0][width / 2]          = ' ';
	//bottom
	charBuffer[height - 1][width / 2] = ' ';
	//left
	charBuffer[height / 2][0]         = ' ';
	//right
	charBuffer[height / 2][width - 1] = ' ';
	
}