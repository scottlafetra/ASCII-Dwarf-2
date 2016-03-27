#pragma once
#include "ASCII-Graphics.h"

using namespace ASCII;

Graphic::Graphic(const int& width, const int& height)
: width(width), height(height), charBuffer(height, vector<char>(width)), chromaBuffer(height, vector<char>(width)) {
	
	position.x = 0;
	position.y = 0;

	clear();
}



Graphic::Graphic(const int& width, const int& height, vector<vector<char>> initCharBuffer, vector<vector<char>> initChromaBuffer) {
	Graphic(width, height);

	chromaBuffer = initChromaBuffer;
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

vector<vector<char>> const Graphic::getCharBuffer() const {
	return charBuffer;
}

vector<vector<char>> const Graphic::getChromaBuffer() const {
	return chromaBuffer;
}

void Graphic::clear(bool clearChroma) {

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {

			charBuffer[y][x] = ' ';
			if (clearChroma)
				chromaBuffer[y][x] = 0x01;
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

			charBuffer[drawPos.y + y][drawPos.x + x] = toDraw.charBuffer[y][x];
			chromaBuffer[drawPos.y + y][drawPos.x + x] = toDraw.chromaBuffer[y][x];
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

				if (toDraw.charBuffer[y][x] != ' ') {
					charBuffer[drawPos.y + y][drawPos.x + x] = toDraw.charBuffer[y][x];
				}
				if (toDraw.chromaBuffer[y][x] != 0x00) {
					chromaBuffer[drawPos.y + y][drawPos.x + x] = toDraw.chromaBuffer[y][x];
				}
			}
		}
}


void Graphic::flush() const {
	for (int y = 0; y < height; ++y) {

		for (int x = 0; x < width; ++x) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), chromaBuffer[y][x]);
			cout<< charBuffer[y][x];
		}
	}
}

int Graphic::getWidth() const {
	return width;
}

int Graphic::getHeight() const {
	return height;
}

WalkingGraphic::WalkingGraphic(const int& width, const int& height)
: Graphic(width, height) {}

WalkingGraphic::WalkingGraphic(const int& width, const int& height, vector<vector<char>> initCharBuffer, vector<vector<char>> chromaBuffer)
: Graphic(width, height, initCharBuffer, chromaBuffer) {}

WalkingGraphic::WalkingGraphic(const int& width, const int& height, vector<vector<char>> initCharBuffer, char color)
: WalkingGraphic(width, height, initCharBuffer, vector<vector<char>>(height, vector<char>(width, color))) {

}

void WalkingGraphic::jump(const int& dx, const int& dy, Graphic& canvas) {
	Graphic shadow(getWidth(), getHeight());//create a shadow to delete
	shadow.moveTo(getPosition().x, getPosition().y);

	canvas.draw(shadow);

	move(dx, dy);

	canvas.draw(*this);
}

void WalkingGraphic::jumpTo(const int& x, const int& y, Graphic& canvas) {
	Graphic shadow(getWidth(), getHeight());//create a shadow to delete
	shadow.moveTo(getPosition().x, getPosition().y);

	canvas.draw(shadow);

	moveTo(x, y);

	canvas.draw(*this);
}

void WalkingGraphic::walk(const int& dx, const int& dy, Graphic& canvas) {

	if (canvas.getCharBuffer()[getPosition().y + dy][getPosition().x + dx] == ' ') {
		jump(dx, dy, canvas);
	}
}