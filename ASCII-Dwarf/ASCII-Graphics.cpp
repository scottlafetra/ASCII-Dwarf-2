#pragma once
#include "ASCII-Graphics.h"

using namespace ASCII;

Graphic::Graphic(const int& width, const int& height)
: width(width), height(height), charBuffer(height, vector<char>(width)) {
	
	position.x = 0;
	position.y = 0;

	clear();
}

Graphic::Graphic(const int& width, const int& height, vector<vector<char>> initCharBuffer) {
	Graphic(width, height);

	charBuffer = initCharBuffer;
	Graphic::width  = width;
	Graphic::height = height;
}

void Graphic::move(const int& dx, const int& dy) {
	position.x += dx;
	position.y += dy;
}

void Graphic::moveTo(const int& x, const int& y) {
	position.x = x;
	position.y = y;
}

const Coordinate Graphic::getPosition() const {
	return position;
}

vector<vector<char>> const Graphic::getBuffer() const {
	return charBuffer;
}

void Graphic::clear() {

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {

			charBuffer[y][x] = ' ';
		}
	}
}

void Graphic::draw(const Graphic& toDraw) {

	Coordinate drawPos = toDraw.getPosition();

	int yInit = max(0, -drawPos.y);
	int yMax = min(height - drawPos.y, toDraw.getHeight());

	int xInit = max(0, -drawPos.x);
	int xMax = min(width - drawPos.x, toDraw.getWidth());

	for (int y = yInit; y < yMax; ++y) {
		for (int x = xInit; x < xMax; ++x) {

			charBuffer[drawPos.y + y][drawPos.x + x] = toDraw.getBuffer()[y][x];
		}
	}
}

void Graphic::drawWithAlpha(const Graphic& toDraw) {

		Coordinate drawPos = toDraw.getPosition();

		int yInit = max(0, -drawPos.y);
		int yMax = min(height - drawPos.y, toDraw.getHeight());

		int xInit = max(0, -drawPos.x);
		int xMax = min(width - drawPos.x, toDraw.getWidth());

		for (int y = yInit; y < yMax; ++y) {
			for (int x = xInit; x < xMax; ++x) {

				if (toDraw.getBuffer()[y][x] != ' ') {
					charBuffer[drawPos.y + y][drawPos.x + x] = toDraw.getBuffer()[y][x];
				}
			}
		}
}


void Graphic::flush() const {

	string flushString = "";
	

	for (int y = 0; y < height; ++y) {

		for (int x = 0; x < width; ++x) {

			flushString += charBuffer[y][x];
		}
	}

	cout << flushString << endl;

}

int Graphic::getWidth() const {
	return width;
}

int Graphic::getHeight() const {
	return height;
}

JumpingGraphic::JumpingGraphic(const int& width, const int& height)
: Graphic(width, height) {}

JumpingGraphic::JumpingGraphic(const int& width, const int& height, vector<vector<char>> initCharBuffer)
: Graphic(width, height, initCharBuffer) {}

void JumpingGraphic::jump(const int& dx, const int& dy, Graphic& canvas) {
	Graphic shadow(getWidth(), getHeight());//create a shadow to delete
	shadow.moveTo(getPosition().x, getPosition().y);

	canvas.draw(shadow);

	move(dx, dy);

	canvas.draw(*this);
}

void JumpingGraphic::jumpTo(const int& x, const int& y, Graphic& canvas) {
	Graphic shadow(getWidth(), getHeight());//create a shadow to delete
	shadow.moveTo(getPosition().x, getPosition().y);

	canvas.draw(shadow);

	moveTo(x, y);

	canvas.draw(*this);
}