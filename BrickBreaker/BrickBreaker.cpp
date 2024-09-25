#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void clearScreen() {
	std::cout << "\033[2J\033[1;1H";
}

void BoardField() {

	char fieldArray[20][27] = {};
	int paddleStart = 11;  // The starting position of the paddle (left-most part)
	int paddleLength = 5;  // Length of the paddle
	char input = '\0';     // Store user input




	while (true) {

		clearScreen();

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 27; j++) {
				fieldArray[i][j] = ' ';
			}
		}

		for (int v = 1; v < 7; v++) {
			for (int z = 1; z < 27; z++) {
				fieldArray[v][z] = '*';
			}
		}

		if (_kbhit()) {
			input = _getch();
			if (input == 'a' && paddleStart > 1) {
				paddleStart--;  // Move paddle left
			}
			if (input == 'd' && paddleStart + paddleLength < 26) {
				paddleStart++;  // Move paddle right
			}
		}
		// Place the paddle at the new position
		for (int j = paddleStart; j < paddleStart + paddleLength; j++) {
			fieldArray[18][j] = '=';  // Draw paddle on the second-to-last row
		}



		fieldArray[17][paddleStart + 2] = 'o';

		for (int a = 0; a < 27; a++) {
			int firstRow = 0;
			int lastRow = 19;
			fieldArray[firstRow][a] = '#';
			fieldArray[lastRow][a] = '#';
		}

		for (int b = 0; b < 20; b++) {
			int firstColumn = 0;
			int lastColumn = 26;
			fieldArray[b][firstColumn] = '#';
			fieldArray[b][lastColumn] = '#';
		}


		for (int i = 0; i < 20; i++) {
			cout << endl;
			for (int j = 0; j < 27; j++) {
				cout << fieldArray[i][j];
			}
		}

		Sleep(100);
	}
}



int main()
{
		BoardField();
}

