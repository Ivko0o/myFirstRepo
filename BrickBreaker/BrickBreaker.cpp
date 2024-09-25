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

	int ballX = 17;  // Ball's initial row position
	int ballY = paddleStart + 2;  // Ball's initial column position (centered on the paddle)
	int ballDirX = -1;  // Ball moving up initially (row direction)
	int ballDirY = 1;   // Ball moving right initially (column direction)

	int scoreBoard = 0;


	while (true) {

		clearScreen();

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 27; j++) {
				fieldArray[i][j] = ' ';
			}
		}

		for (int brickPositionX = 1; brickPositionX < 7; brickPositionX++) {
			for (int brickPositionY = 1; brickPositionY < 27; brickPositionY++) {
				fieldArray[brickPositionX][brickPositionY] = '*';
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

		ballX += ballDirX;
		ballY += ballDirY;

		// Check for ball collisions with walls and paddle
		if (ballX <= 0) {  // Ball hits the top wall
			ballDirX = 1;  // Bounce down
		}
		if (ballY <= 1 || ballY >= 25) {  // Ball hits the left or right wall
			ballDirY = -ballDirY;  // Reverse horizontal direction
		}
		if (ballX == 18 && ballY >= paddleStart && ballY < paddleStart + paddleLength) {  // Ball hits the paddle
			ballDirX = -1;  // Bounce up
		}


		if (ballX > 1 && ballX < 7) {                           // This was made by Ivelin so the 'o' can hit the bricks
			ballDirX = 1;
			fieldArray[6][2] = ' ';
			scoreBoard += 10;
		}
		


		// Ball reaches the bottom (lose condition or reset)
		if (ballX >= 19) {
			ballX = 17;  // Reset ball to above the paddle
			ballY = paddleStart + 2;  // Center ball above the paddle
			ballDirX = -1;  // Ball moves up again
			ballDirY = 1;  // Ball moves right
			cout << "Game over!" << endl;                          // This was built by Ivelin so the game can end. If you remove it, the game will constantly loop.
			cout << "Your score is: " << scoreBoard;
			break;
		}


		// Place the ball at the new position
		fieldArray[ballX][ballY] = 'o';


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

