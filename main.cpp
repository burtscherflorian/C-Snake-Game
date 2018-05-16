#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;
bool gameOver;
const int width = 40;
const int height = 20;
bool retry = true;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	nTail = 0;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw() {
	system("cls"); //system("clear"); for LINUX
	cout << "\033[1;31mSNAKE by burtscherflorian\033[0m\n";
	cout << "\033[1;31mcredits to NVitanovic\033[0m\n";
	cout << "https://www.youtube.com/watch?v=E_-lMZDi7Uw" << endl;
	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+1; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input() {
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'a':
				dir != RIGHT ? dir = LEFT : dir = RIGHT;
				break;

			case 'd':
				dir != LEFT ? dir = RIGHT: dir = LEFT;
				break;

			case 'w':
				dir != DOWN ? dir = UP : dir = DOWN;
				break;

			case 's':
				dir != UP ? dir = DOWN : dir = UP;
				break;

			case 'x':
				gameOver = true;

			default:
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

	for (int i = 1; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
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
	}
	
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;

	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

void game() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(80);
	}
	Sleep(1000);
	cout << "GAME OVER" << endl;
	Sleep(1000);
	cout << "Press N for new game or X to quit..." << endl;
	retry = true;
	while (retry){
		if (_kbhit) {
			if (_getch() == 'n') {
				retry = false;
				game();
			}
			else if (_getch() == 'x') {
				retry = false;
			}
			else
				retry = true;
		}
	}
}


int main() 
{
	game();
	return 0;
}
