#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int ROWS = 20;
const int COLS = 27;
const int HM_ROWS = 7;
const int HM_COLS = 26;

void ClearScreen();
void InitMap(char hitMap[HM_ROWS][HM_COLS], char fieldArray[ROWS][COLS], int rows, int cols);
void InitializeBricks(char hitMap[][HM_COLS]);
void MovePaddle(char fieldArray[][COLS], int paddlePos_x, int paddleSize);
void MoveBall(char fieldArray[][COLS], int paddlePos_x, int paddleSize, int* ballX, int* ballY, int* ballDirX, int* ballDirY);
void BrickCollision(char fieldArray[][COLS], int ballY, int ballX);
bool CheckGameEnd(int ballY);
//void BallAndPaddleMovement(char hitMap[][HM_COLS], char fieldArray[][COLS], int paddleBeginning, int paddleSize, char userInput, int ballInitX, int ballInitY, int ballDirectionX, int ballDirectionY, int highscore);
void PrintField(char fieldArray[][COLS]);
void ProcessInput(int* paddlePos_x, int paddleLength);

int main()
{
	char fieldArray[ROWS][COLS] = {};
	char hitMap[HM_ROWS][HM_COLS] = {};

	int paddlePos_x = 11;  // The starting position of the paddle (left-most part)
	int paddleSize = 5;  // Length of the paddle
	char input = '\0';     // Store user input

	int ballY = 17;  // Ball's initial row position
	int ballX = paddlePos_x + 2;  // Ball's initial column position (centered on the paddle)
	int ballDirY = -1;  // Ball moving up initially (row direction)
	int ballDirX = 1;   // Ball moving right initially (column direction)

	int scoreBoard = 0;

	while (true) {
		ClearScreen();
		InitMap(hitMap, fieldArray, ROWS, COLS);
		InitializeBricks(hitMap);
		ProcessInput(&paddlePos_x, paddleSize);
		MovePaddle(fieldArray, paddlePos_x, paddleSize);
		MoveBall(fieldArray, paddlePos_x, paddleSize, &ballX, &ballY, &ballDirX, &ballDirY);
		BrickCollision(fieldArray, ballY, ballX);
		PrintField(fieldArray);
		if (CheckGameEnd(ballY) == false)
			return false;
		Sleep(100);
	}


	/* for (int i = 0; i < HM_ROWS; i++) {
	for (int j = 1; j < HM_COLS; j++) {										���� ���� �� � �������
		hitMap[i][j] = '*';
	} */
}

void ClearScreen() {
	std::cout << "\033[2J\033[1;1H";
}

void InitMap(char hitMap[HM_ROWS][HM_COLS], char fieldArray[ROWS][COLS], int rows, int cols) {

	// Fills field with empty spaces
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			fieldArray[i][j] = ' ';
		}
	}
	// Place the bricks
	for (int brickPositionX = 1; brickPositionX < 7; brickPositionX++) {
		for (int brickPositionY = 1; brickPositionY < COLS; brickPositionY++) {
			fieldArray[brickPositionX][brickPositionY] = '*';
		}
	}

	// Place top and bottom borders
	for (int a = 0; a < COLS; a++) {
		int firstRow = 0;
		int lastRow = rows-1;
		fieldArray[firstRow][a] = '#';
		fieldArray[lastRow][a] = '#';
	}

	 // Place left and right borders
	for (int b = 0; b < ROWS; b++) {
		int firstColumn = 0;
		int lastColumn = cols-1;
		fieldArray[b][firstColumn] = '#';
		fieldArray[b][lastColumn] = '#';
	}
}

void InitializeBricks(char hitMap[][HM_COLS]) {

	// Initializing the bricks in the game field
	for (int i = 0; i < HM_ROWS; i++) {
		for (int j = 1; j < HM_COLS; j++) {
			hitMap[i][j] = '*';
		}
	}
}

void ProcessInput(int* paddlePos_x, int paddleLength)
{
		if (_kbhit()) {
			char userInput = _getch();
			if (userInput == 'a' && *paddlePos_x > 1) {
				(*paddlePos_x)--;  // Move paddle left
			}
			if (userInput == 'd' && *paddlePos_x + paddleLength < 26) {
				(*paddlePos_x)++;  // Move paddle right
			}
		}
}

void MovePaddle(char fieldArray[][COLS], int paddlePos_x, int paddleSize) {
	// Place the paddle at the new position
	for (int j = paddlePos_x; j < paddlePos_x + paddleSize; j++) {
		fieldArray[18][j] = '=';  // Draw paddle on the second-to-last row
	}
}

void MoveBall(char fieldArray[][COLS],int paddlePos_x, int paddleSize, int* ballX, int* ballY, int* ballDirX, int* ballDirY) {

	fieldArray[*ballY][*ballX] = 'o';

	*ballX += *ballDirX;
	*ballY += *ballDirY;

	// Check for ball collisions with walls and paddle
		// walls
	if (*ballY <= 0) {  // Ball hits the top wall
		*ballDirY = 1;  // Bounce down
	}
	if (*ballX <= 1 || *ballX >= 25) {  // Ball hits the left or right wall
		*ballDirX = -(*ballDirX);  // Reverse horizontal direction
	}

	// Paddle
	if (*ballY == 18 && *ballX >= paddlePos_x && *ballDirX < paddlePos_x + paddleSize) {  // Ball hits the paddle
		*ballDirY = -1;  // Bounce up
	}
	
}
void BrickCollision(char fieldArray[][COLS], int ballY, int ballX) {
	if (ballY < HM_ROWS && ballY >=0 && ballX < HM_COLS && ballX >= 0) {
		if (fieldArray[ballY][ballX] == '*')
			fieldArray[ballY][ballX] = ' ';
	}
}

bool CheckGameEnd(int ballY) {
	if (ballY >= 19) {
		cout << "Game over!" << endl;
		return false;
	}
}

/* void BallAndPaddleMovement(char hitMap[][HM_COLS], char fieldArray[][COLS], int paddlePos_x, int paddleSize, char userInput, int ballInitX, int ballInitY, int ballDirectionX, int ballDirectionY, int highscore) {

		

		ballInitX += ballDirectionX;
		ballInitY += ballDirectionY;

		// Check for ball collisions with walls and paddle
		if (ballInitX <= 0) {  // Ball hits the top wall
			ballDirectionX = 1;  // Bounce down
		}
		if (ballInitY <= 1 || ballInitY >= 25) {  // Ball hits the left or right wall
			ballDirectionY = -ballDirectionY;  // Reverse horizontal direction
		}
		if (ballInitX == 18 && ballInitY >= paddlePos_x && ballInitY < paddlePos_x + paddleSize) {  // Ball hits the paddle
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
			ballInitY = paddlePos_x + 2;  // Center ball above the paddle
			ballDirectionX = -1;  // Ball moves up again
			ballDirectionY = 1;  // Ball moves right
			cout << "Game over!" << endl;                          // This was built by Ivelin so the game can end. If you remove it, the game will constantly loop.
			cout << "Your score is: " << highscore;
			break;
		}


		// Place the ball at the new position
		fieldArray[ballInitX][ballInitY] = 'o';
	}

} */

void PrintField(char fieldArray[][COLS]) {
	// Print the field
	for (int i = 0; i < ROWS; i++) {
		cout << endl;
		for (int j = 0; j < COLS; j++) {
			cout << fieldArray[i][j];
		}
	}
}
