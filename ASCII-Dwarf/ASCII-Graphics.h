#pragma once
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using namespace std;

namespace ASCII {

	struct Coordinate {
		int x;
		int y;
	};

	class Graphic {
	private:
		int width;
		int height;

		Coordinate position;

	protected:
		vector<vector<char>> charBuffer;
		vector<vector<char>> chromaBuffer;

	public:
		Graphic(const int& width, const int& height);
		Graphic(const int& width, const int& height, vector<vector<char>> initCharBuffer, vector<vector<char>>);

		void move(const int& dx, const int& dy);
		void moveTo(const int& x, const int& y);

		const Coordinate getPosition() const;
		vector<vector<char>> const getCharBuffer() const;
		vector<vector<char>> const getChromaBuffer() const;

		int getWidth() const;
		int getHeight() const;

		void clear(bool clearChroma = true);

		void draw(const Graphic& toDraw);
		void drawWithAlpha(const Graphic& toDraw);
		void flush() const;
	};

	class WalkingGraphic : public Graphic {
	public:
		WalkingGraphic(const int& width, const int& height);
		WalkingGraphic(const int& width, const int& height, vector<vector<char>> initCharBuffer, vector<vector<char>> chromaBuffer);
		WalkingGraphic(const int& width, const int& height, vector<vector<char>> initCharBuffer, char color);

		void jump(const int& dx, const int& dy, Graphic& canvas);
		void jumpTo(const int& x, const int& y, Graphic& canvas);

		void walk(const int& dx, const int& dy, Graphic& canvas);
	};
}

