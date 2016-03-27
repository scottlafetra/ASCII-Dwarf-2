#pragma once
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

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

		vector<vector<char>> charBuffer;

		Coordinate position;

	public:
		Graphic(const int& width, const int& height);
		Graphic(const int& width, const int& height, vector<vector<char>> initCharBuffer);

		void move(const int& dx, const int& dy);
		void moveTo(const int& x, const int& y);

		const Coordinate getPosition() const;
		vector<vector<char>> const getBuffer() const;

		int getWidth() const;
		int getHeight() const;

		void clear();
		void draw(const Graphic& toDraw);
		void drawWithAlpha(const Graphic& toDraw);
		void flush() const;
	};

	class JumpingGraphic : Graphic {
	public:
		JumpingGraphic(const int& width, const int& height);
		JumpingGraphic(const int& width, const int& height, vector<vector<char>> initCharBuffer);

		void jump(const int& dx, const int& dy, Graphic& canvas);
		void jumpTo(const int& x, const int& y, Graphic& canvas);
	};
}

