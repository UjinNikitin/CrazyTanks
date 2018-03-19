// CrazyTanks.cpp: главный файл проекта.

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cmath>

//#include <stdio.h>

using namespace std;

bool gameOver;
bool shot;
const int width = 60;
const int height = 40;
int x, y, score;
int bulletX;
int bulletY;
int lastXY[2];
int arrWallsX[10];
int arrWallsY[10];
int arrWallsPointsX[10][5];
int arrWallsPointsY[10][5];
int enemyTanksX[6];
int enemyTanksY[6];
int lastEnemyTanksX[6];
int lastEnemyTanksY[6];
int shotsCout;
int timeG = 0;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection bulletFlight;

/*class Tank {
public:
	int hp;

	Tank(int a) : hp(a)
	{}

};*/


void deadlyShot(int direction) {

}


void selectSort(int* arr, int size){
	int tmp;
	for (int i = 0; i < size; i++)
	{
		int pos = i;
		tmp = arr[i];
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < tmp)
			{
				pos = j;
				tmp = arr[j];
			}
		}
		arr[pos] = arr[i];
		arr[i] = tmp;
	}
}


void setup() {
	gameOver = false;
	shot = false;
	x = width / 2;
	y = height - 1;
	score = 0;
	srand(time(NULL));
	bulletFlight = STOP;
	bulletX = 62;
	shotsCout = 0;
	
	for (int i = 0; i < 10; i++) {
		arrWallsX[i] = 1 + rand() % 4;
		arrWallsY[i] = 1 + rand() % 4;
		arrWallsPointsX[i][0] = rand() % 55;
		arrWallsPointsY[i][0] = rand() % 35;
		arrWallsPointsX[i][4] = rand() % 35;
		arrWallsPointsY[i][4] = rand() % 55;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 1; j < arrWallsX[i]; j++) {
			arrWallsPointsX[i][j] = arrWallsPointsX[i][0] + j;
		}
		for (int j = 1; j < arrWallsY[i]; j++) 
			arrWallsPointsY[i][j] = arrWallsPointsY[i][0] + j;
	}

	for (int i = 0; i < 6; i++) {
		enemyTanksX[i] = 1 + rand() % (width - 2);
		enemyTanksY[i] = 1 + rand() % (height - 1);
	}

	bool correctRand = false;
	while (!correctRand) {
		selectSort(enemyTanksX, 6);
		selectSort(enemyTanksY, 6);

		for (int i = 0; i < 6; i++) {

			for (int k = 0; k < 10; k++) {
				for (int j = 0; j < 5; j++) {
					if (enemyTanksX[i] == arrWallsPointsX[k][j] || enemyTanksX[i] == arrWallsPointsY[k][j])
						enemyTanksX[i] = 1 + rand() % (width - 2);
				}
				for (int j = 0; j < 5; j++) {
					if (enemyTanksY[i] == arrWallsPointsX[k][j] || enemyTanksY[i] == arrWallsPointsY[k][j])
						enemyTanksY[i] = 1 + rand() % (height - 1);
				}
			}
		}
for (int i = 0; i < 5; i++) {
	selectSort(enemyTanksX, 6);
	selectSort(enemyTanksY, 6);

	if (enemyTanksX[i + 1] - enemyTanksX[i] <= 2)
		enemyTanksX[i + 1] = 1 + rand() % (width - 2);
	else {
		if (enemyTanksY[i + 1] - enemyTanksY[i] <= 2)
			enemyTanksY[i + 1] = 1 + rand() % (height - 1);
		else
			correctRand = true;
	}
}
	}

	/*
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			cout << arrWallsPointsX[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			cout << arrWallsPointsY[i][j] << "  ";
		}
		cout << endl;
	}*/

}


void input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 72:
			lastXY[0] = y;
			y--;
			bulletFlight = UP;
			break;
		case 80:
			lastXY[0] = y;
			y++;
			bulletFlight = DOWN;
			break;
		case 75:
			lastXY[1] = x;
			x--;
			bulletFlight = LEFT;
			break;
		case 77:
			lastXY[1] = x;
			x++;
			bulletFlight = RIGHT;
			break;
		case 32:
			shotsCout++;
			shot = true;
			break;
		case 'r':
			gameOver = true;
			break;
		}
	}
}


void logic() {
	if (x < 0 || x > width - 2)
		x = lastXY[1];
	if (y < 0 || y > height - 1)
		y = lastXY[0];
	if (shot) {
		switch (bulletFlight)
		{
		case UP:
			bulletY--;
			break;
		case DOWN:
			bulletY++;
			break;
		case LEFT:
			bulletX--;
			break;
		case RIGHT:
			bulletX++;
			break;
		}
	}
	else {
		bulletX = x;
		bulletY = y;
	}

	for (int q = 0; q < 10; q++) {
		for (int m = 0; m < 4; m++) {
			if (y == arrWallsPointsX[q][4] && x == arrWallsPointsX[q][m])
				y = lastXY[0];
			if (x == arrWallsPointsY[q][4] && y == arrWallsPointsY[q][m])
				x = lastXY[1];
		}
	}
	if (bulletX < 0 || bulletX > width - 2 || bulletY < 0 || bulletY > height - 1)
		shot = false;
	for (int i = 0; i < 6; i++) {
		lastEnemyTanksX[i] = enemyTanksX[i];
		lastEnemyTanksY[i] = enemyTanksY[i];
		if (abs(enemyTanksX[i] - x) < abs(enemyTanksY[i] - y) && (enemyTanksX[i] - x) > 0) {
			lastEnemyTanksX[i] = enemyTanksX[i];
			enemyTanksX[i]--;
		}
		if (abs(enemyTanksX[i] - x) < abs(enemyTanksY[i] - y) && (enemyTanksX[i] - x) < 0) {
			lastEnemyTanksX[i] = enemyTanksX[i];
			enemyTanksX[i]++;
		}
		if (abs(enemyTanksX[i] - x) > abs(enemyTanksY[i] - y) && (enemyTanksY[i] - y) < 0) {
			lastEnemyTanksY[i] = enemyTanksY[i];
			enemyTanksY[i]++;
		}
		if (abs(enemyTanksX[i] - x) > abs(enemyTanksY[i] - y) && (enemyTanksY[i] - y) > 0) {
			lastEnemyTanksY[i] = enemyTanksY[i];
			enemyTanksY[i]--;
		}
		for (int q = 0; q < 10; q++) {
			for (int m = 0; m < 4; m++) {
				if (enemyTanksY[i] == arrWallsPointsX[q][4] && enemyTanksX[i] == arrWallsPointsX[q][m])
					enemyTanksY[i] = lastEnemyTanksX[i];
				if (enemyTanksX[i] == arrWallsPointsY[q][4] && enemyTanksY[i] == arrWallsPointsY[q][m])
					enemyTanksX[i] = lastEnemyTanksY[i];
			}
		}
	}
}

void draw(){
	system("cls");
	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "@";
			else {
				bool mightPass = false;
				int k = 0;
				for (int q = 0; q < 10; q++) {
					for (int m = 0; m < 4; m++) {
						if (i == 0 || j == 0) continue;
						if ((i == arrWallsPointsX[q][4] && j == arrWallsPointsX[q][m]) || (j == arrWallsPointsY[q][4] && i == arrWallsPointsY[q][m])){
							cout << "#";
							k = 6;
							mightPass = true;
							m = 4;
							q = 10;
						}
					}
				}
				if (shot && !mightPass && i == bulletY && j == bulletX) {
					k = 6;
					mightPass = true;
					cout << "Х";
				}

				for (k; k < 6; k++) {
					if (i == enemyTanksY[k] && j == enemyTanksX[k]) {
						k = 6;
						mightPass = true;
						cout << "O";
					}
				}
				if (!mightPass)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
	cout << "Time: " << timeG << " ms" << endl;
	cout << "Press 'R' to leave the game";
}



int main() {
	setup();
	while (!gameOver) {
		int start = GetTickCount();
		input();
		logic();
		draw();
		int end = GetTickCount();
		timeG = (timeG + end - start);
	}
	return 0;
}
