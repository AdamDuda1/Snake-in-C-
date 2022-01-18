#include "connecter.h"

using namespace std;

bool GameOver;
const int widht = 40, height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup() {
	GameOver = false;
	dir = STOP;
	x = widht / 2;
	y = height / 2;
	fruitX = rand() % widht;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("CLS");

	for (int i = 0; i < widht+1; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < widht; j++)
		{
			if (j == 0) {
				cout << "#";
			}
			if (i == y && j == x) {
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}
			}

			if (j == widht - 1) {
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < widht+1; i++)
	{
		cout << "#";
	}
	cout << endl << "Score: " << score;
}

void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
		dir = LEFT;
			break;
		case 'd':
		dir = RIGHT;
			break;
		case 'w':
		dir = UP;
			break;
		case 's':
		dir = DOWN;
			break;
		case 'x':
			GameOver = true;
			break;
		}
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 0; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x > widht || x < 0 || y > height || y < 0) {
		GameOver = true;
	}
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % widht;
		fruitY = rand() % height;
		nTail++;
	}
}

//na póŸniej : przenieœæ do pliku main z bool gameover

int main() {
	Setup();
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(35);
	}
}