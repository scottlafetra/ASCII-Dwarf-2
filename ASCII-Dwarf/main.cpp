#include "ASCII-Graphics.h"
#include "windows.h"
#include <iostream>
#include <vector>

using namespace std;


int main() {
	//80 x 25
	
	ASCII::Graphic screenBuffer(80, 23);

	vector<vector<char>> square = {
		{ '#', '-', '#' },
		{ '|', ' ', '|' },
		{ '#', '-', '#' }
	};
	
	ASCII::Graphic testsquare(3, 3, square);
	
	testsquare.moveTo(10, 10);

	screenBuffer.draw(testsquare);

	screenBuffer.flush();

	


	system("pause");
	return 0;
}