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
void BrickCollision(char hitMap[][HM_COLS], int ballY, int ballX, int* ballDirY);
void CountScore(char hitMap[][HM_COLS]);
bool CheckGameEnd(int ballY);
void PrintField(char fieldArray[][COLS], char hm[][HM_COLS]);
void ProcessInput(int* paddlePos_x, int paddleLength);

int main()
{
	char fieldArray[ROWS][COLS] = {};
	char hitMap[HM_ROWS][HM_COLS] = {};

	int paddlePos_x = 11;  // The starting position of the paddle (left-most part)
	int paddleSize = 5;  // Length of the paddle

	int ballY = 17;  // Ball's initial row position
	int ballX = paddlePos_x + 2;  // Ball's initial column position (centered on the paddle)
	int ballDirY = -1;  // Ball moving up initially (row direction)
	int ballDirX = 1;   // Ball moving right initially (column direction)

	InitializeBricks(hitMap);

	while (CheckGameEnd(ballY)){
		ClearScreen();
		InitMap(hitMap, fieldArray, ROWS, COLS);
		ProcessInput(&paddlePos_x, paddleSize);
		MovePaddle(fieldArray, paddlePos_x, paddleSize);
		MoveBall(fieldArray, paddlePos_x, paddleSize, &ballX, &ballY, &ballDirX, &ballDirY);
		BrickCollision(hitMap, ballY, ballX, &ballDirY);
		PrintField(fieldArray, hitMap);
		if (CheckGameEnd(ballY) == false)
			break;
		Sleep(100);
	}
	CountScore(hitMap);
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
			if (hitMap[brickPositionX][brickPositionY] == '.' )
				continue;
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
	if (*ballY <= 1) {  // Ball hits the top wall
		*ballDirY = 1;  // Bounce down
	}
	if (*ballX <= 1 || *ballX >= 25) {  // Ball hits the left or right wall
		*ballDirX = -(*ballDirX);  // Reverse horizontal direction
	}

	// Paddle
	if (*ballY == 18 && *ballX >= paddlePos_x && *ballX < paddlePos_x + paddleSize) {  // Ball hits the paddle
		*ballDirY = -1;  // Bounce up
	}


	
}
void BrickCollision(char hitMap[][HM_COLS], int ballY, int ballX, int* ballDirY) {

	// Checks if the ball hits a brick and change the direction
	if (ballY < HM_ROWS && ballY > 0 && ballX < HM_COLS && ballX > 0) {
		if(hitMap[ballY][ballX] == '*') {
			hitMap[ballY][ballX] = '.';
			*ballDirY = -(*ballDirY);
		}
	}
		
	}

void CountScore(char hitMap[][HM_COLS]) {
	int scoreBoard = 0;
	for (int i = 0; i < HM_ROWS; i++) {
		for (int j = 0; j < HM_COLS; j++) {
			if (hitMap[i][j] == '.') {
				scoreBoard += 10;
			}
		}
	}
	cout << "Your score is: " << scoreBoard;
}

bool CheckGameEnd(int ballY) {
	if (ballY >= 19) {
		cout << endl;
		cout << "Game over!" << endl;
		return false;
	}

}

void PrintField(char fieldArray[][COLS], char hm[][HM_COLS]) {
	// Print the field
	for (int i = 0; i < ROWS; i++) {
		cout << endl;
		for (int j = 0; j < COLS; j++) {
			if (fieldArray[i][j] == 'o') {
				cout << "o";
				continue;
			}

			if (hm[i][j] == '.')
			{
				cout << " ";
				continue;
			}				
			cout << fieldArray[i][j];
		}
	}
}
