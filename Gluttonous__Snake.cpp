// 贪吃蛇.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<math.h>

#define high 20
#define width 30
//#define game_speed 10

int canvas[high][width];
int head_x, head_y;
int food_x, food_y;
int tail_x, tail_y;
int i, j;
int direction=4;
int game_speed;
int speed_up;
int game_over;

void startup() {
	head_x = high / 2;
	head_y = width / 2;
	food_x = high / 3;
	food_y = width / 3;
	speed_up = 0;
	int game_over = 0;
	for (i = 0; i < high; ++i) {
		for (j = 0; j < width; ++j)
			canvas[i][j] = 0;
	}
	for (i = 0; i < 3; ++i) {
		canvas[head_x][head_y-i] = 1+i;
	}
	canvas[food_x][food_y] = -1;
}

//光标移动到( x, y ) 
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

// 隐藏光标 
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void show() {
	gotoxy(0,0);
	HideCursor();
	for (i = 0; i < high + 1; i++) {
		for (j = 0; j < width + 1; j++) {
			if (j == width) printf("|");
			else if (i == high) printf("_");
			else if (canvas[i][j] == 1) printf("@");
			else if (canvas[i][j] > 1) printf("#");
			else if (canvas[i][j] == -1) printf("F");
			else if(canvas[i][j]==0) printf(" ");
		}
		printf("\n");
	}
	Sleep(game_speed);
}

int move_direction() {
	char input;
	while (_kbhit()) {
		input = _getch();
		if (input == 'w') return 1;
		else if (input == 's') return 2;
		else if (input == 'a') return 3;
		else if (input == 'd') return 4;
		else if (input == ' ') speed_up = 1;
		else return 0;
	}
	return 0;
}

void produceFood() {
	srand((unsigned)time(NULL));
	int flag = 1;
	while (flag) {
		food_x = rand() % high;
		food_y = rand() % width;
		if (canvas[food_x][food_y] == 0)
			flag = 0;
	}
	canvas[food_x][food_y] = -1;
}


int updata() {
	int move = move_direction();
	
		int max = 0;
		for (i = 0; i < high; ++i) {
			for (j = 0; j < width; ++j) {
				if (canvas[i][j] > max) {
					max = canvas[i][j];
					tail_x = i;
					tail_y = j;
				}			
				if (canvas[i][j] > 0) canvas[i][j]++;
			}
		}
		if (move != 0) {
			if (move == 1) head_x--;
			else if (move == 2) head_x++;
			else if (move == 3) head_y--;
			else if (move == 4) head_y++;
			direction = move;
		}
		else if (move == 0) {
			if (direction == 1) head_x--;
			else if (direction == 2) head_x++;
			else if (direction == 3) head_y--;
			else if (direction == 4) head_y++;
		}
		//防止越界边框
		if (head_x == high) head_x--;
		else if (head_x == -1) head_x++;
		if (head_y == width) head_y--;
		else if (head_y == -1) head_y++;
		if (canvas[head_x][head_y] > 1) ;
		if (canvas[head_x][head_y] == -1) {
			produceFood();
		}
		else canvas[tail_x][tail_y] = 0;
		canvas[head_x][head_y] = 1;
		if(speed_up==0) game_speed = 2000 / max+200;
		else {
			game_speed = 0;
			speed_up = 0;
		}
		return 1;

}




//debug函数, 打印canvas的所有数据
int debug(int num) {
	if (num == 0) return 0;
	else {
		for (i = 0; i < high; ++i) {
			for (j = 0; j < width; ++j)
				printf("%d ", canvas[i][j]);
			printf("\n");
		}
		//system("pause");
		Sleep(game_speed);
		return 1;

	}
}
int main() {
	startup();
	while (game_over) {
		show();
		//debug(1);
		//update_with_input();
		Sleep(100);
		updata();
	}
	system("cls");
	printf("游戏结束\n");
	system("pause");
	return 0;
}
