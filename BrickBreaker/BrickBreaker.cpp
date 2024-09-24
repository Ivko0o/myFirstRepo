#include <iostream>

using namespace std;

void BoardField() {

	char fieldArray[20][26] = {};

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 26; j++) {
			fieldArray[i][j] = ' ';
		}
	}

	for (int v = 1; v < 7; v++) {
		for (int z = 1; z < 25; z++) {
			fieldArray[v][z] = '*';
		}
	}

	for (int j = 11; j < 15; j++) {
		fieldArray[18][j] = '=';
	}

	for (int a = 0; a < 26; a++) {
		int firstRow = 0;
		int lastRow = 19;
		fieldArray[firstRow][a] = '#';
		fieldArray[lastRow][a] = '#';
	}

	for (int b = 0; b < 20; b++) {
		int firstColumn = 0;
		int lastColumn = 25;
		fieldArray[b][firstColumn] = '#';
		fieldArray[b][lastColumn] = '#';
	}


	for (int i = 0; i < 20; i++) {
		cout << endl;
		for (int j = 0; j < 26; j++) {
			cout << fieldArray[i][j];
		}
	}

}

int main()
{
	BoardField();
}

