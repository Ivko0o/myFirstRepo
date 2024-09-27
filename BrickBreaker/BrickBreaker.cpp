#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int ROWS = 20;
const int COLS = 27;
const int HM_ROWS = 7;
const int HM_COLS = 26;

void ClearScreen();
void InitializeMap(char hitMap[HM_ROWS][HM_COLS], char fieldArray[ROWS][COLS], int rows, int cols);
void BallandPaddleMovement(char hitMap[][HM_COLS], char fieldArray[][COLS], int paddleBeginning, int paddleSize, char userInput, int ballInitX, int ballInitY, int ballDirectionX, int ballDirectionY, int highscore);
void PrintField(char fieldArray[][COLS]);

int main()
{
	char fieldArray[ROWS][COLS] = {};
	char hitMap[HM_ROWS][HM_COLS] = {};

	int paddleStart = 11;  // The starting position of the paddle (left-most part)
	int paddleLength = 5;  // Length of the paddle
	char input = '\0';     // Store user input

	int ballX = 17;  // Ball's initial row position
	int ballY = paddleStart + 2;  // Ball's initial column position (centered on the paddle)
	int ballDirX = -1;  // Ball moving up initially (row direction)
	int ballDirY = 1;   // Ball moving right initially (column direction)

	int scoreBoard = 0;

	while (true) {
		ClearScreen();
		InitializeMap(hitMap, fieldArray, ROWS, COLS);
		BallandPaddleMovement(hitMap, fieldArray, paddleStart, paddleLength, input, ballX, ballY, ballDirX, ballDirY, scoreBoard);
		PrintField(fieldArray);
		Sleep(100);
	}


	/* for (int i = 0; i < HM_ROWS; i++) {
	for (int j = 1; j < HM_COLS; j++) {										рнгх кнно ме е днаюбъм
		hitMap[i][j] = '*';
	} */
}

void ClearScreen() {
	std::cout << "\033[2J\033[1;1H";
}

void InitializeMap(char hitMap[HM_ROWS][HM_COLS], char fieldArray[ROWS][COLS], int rows, int cols) {

	// Fills field with empty spaces
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			fieldArray[i][j] = ' ';
		}
	}
	// Place the bricks
	for (int brickPositionX = 1; brickPositionX < 7; brickPositionX++) {
		for (int brickPositionY = 1; brickPositionY < COLS; brickPositionY++) {
			if (hitMap[brickPositionX][brickPositionY] == '.')
				continue;

			fieldArray[brickPositionX][brickPositionY] = '*';
		}
	}

	// Draw the field
	for (int a = 0; a < COLS; a++) {
		int firstRow = 0;
		int lastRow = rows-1;
		fieldArray[firstRow][a] = '#';
		fieldArray[lastRow][a] = '#';
	}

	// Draw the field
	for (int b = 0; b < ROWS; b++) {
		int firstColumn = 0;
		int lastColumn = cols-1;
		fieldArray[b][firstColumn] = '#';
		fieldArray[b][lastColumn] = '#';
	}


}

void BallandPaddleMovement(char hitMap[][HM_COLS], char fieldArray[][COLS], int paddleBeginning, int paddleSize, char userInput, int ballInitX, int ballInitY, int ballDirectionX, int ballDirectionY, int highscore) {
	
		if (_kbhit()) {
			userInput = _getch();
			if (userInput == 'a' && paddleBeginning > 1) {
				paddleBeginning--;  // Move paddle left
			}
			if (userInput == 'd' && paddleBeginning + paddleSize < 26) {
				paddleBeginning++;  // Move paddle right
			}
		}
		// Place the paddle at the new position
		for (int j = paddleBeginning; j < paddleBeginning + paddleSize; j++) {
			fieldArray[18][j] = '=';  // Draw paddle on the second-to-last row


		ballInitX += ballDirectionX;
		ballInitY += ballDirectionY;

		// Check for ball collisions with walls and paddle
		if (ballInitX <= 0) {  // Ball hits the top wall
			ballDirectionX = 1;  // Bounce down
		}
		if (ballInitY <= 1 || ballInitY >= 25) {  // Ball hits the left or right wall
			ballDirectionY = -ballDirectionY;  // Reverse horizontal direction
		}
		if (ballInitX == 18 && ballInitY >= paddleBeginning && ballInitY < paddleBeginning + paddleSize) {  // Ball hits the paddle
			ballDirectionX = -1;  // Bounce up
		}


		if (ballInitX > 1 && ballInitX < 7) {                           // This was made by Ivelin so the 'o' can hit the bricks
			if (hitMap[ballInitX][ballInitY] == '*') {
				ballDirectionX = -ballDirectionX;
				hitMap[ballInitX][ballInitY] = '.';
				highscore += 10;
			}
		}



		// Ball reaches the bottom (lose condition or reset)
		if (ballInitX >= 19) {
			ballInitX = 17;  // Reset ball to above the paddle
			ballInitY = paddleBeginning + 2;  // Center ball above the paddle
			ballDirectionX = -1;  // Ball moves up again
			ballDirectionY = 1;  // Ball moves right
			cout << "Game over!" << endl;                          // This was built by Ivelin so the game can end. If you remove it, the game will constantly loop.
			cout << "Your score is: " << highscore;
			break;
		}


		// Place the ball at the new position
		fieldArray[ballInitX][ballInitY] = 'o';
	}

}

void PrintField(char fieldArray[][COLS]) {
	// Print the field
	for (int i = 0; i < ROWS; i++) {
		cout << endl;
		for (int j = 0; j < COLS; j++) {
			cout << fieldArray[i][j];
		}
	}
}
