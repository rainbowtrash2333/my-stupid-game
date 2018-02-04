/*
    ***消方块***
***A D 控制挡板移动*** 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//全局变量
#define high 20
#define width 30
#define obj_high 3
int i, j;
int objects[obj_high][width];
int board_y,board_width;
//球的位置及方向
typedef struct Ball {
	int x;
	int y;
	int vector_x;
	int vector_y;
}Ball;
Ball ball;

//数据初始化
void startup() {
	ball.x = high / 2;
	ball.y = width / 2 ;
	//球X Y 方向为正
	ball.vector_x = 1;
	ball.vector_y = 1;
	board_width = 5;
	board_y = (width - board_width) / 2 ;
	//object初始化为1
	for (i = 0; i < obj_high*width; i++)
		*(objects[0]+i) = 1;
}

//光标移动到(x,y)位置
void gotoxy(int x, int y)  
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//打印图形
void show() {
//	system("cls");
	gotoxy(0, 0);
	for (i = 0; i < high+1; i++) {
		for (j = 0; j < width+1; j++) {
			
			//打印ball
			if ((i == ball.x)&& (j == ball.y)) 
            	printf("@");
			
			//打印边框
			else if (i == high) printf("_");
			else if (j == width) printf("|");
			
			//打印objects
			else if ((i < obj_high)&& (objects[i][j]))
					printf("*");

			//打印board
			else if ((i == high-1)&& (j < board_width + board_y) && (j >= board_y))
					printf("-");
			else
				printf(" ");
		}
		printf("\n");
	}
	Sleep(50);
}

//ball移动速度控制
int BallSpeedControl(int speed_num) {
	static int n = 0;
	++n;
	if (n == speed_num) {
		n = 0;
		return 1;
	}

	else
		return 0;
}

//不受玩家的更新
void UpdataWithoutInput() {
	
	if (BallSpeedControl(3)) {
	
		//消除object 和反弹
		if ((ball.x < obj_high)&&(objects[ball.x][ball.y])) {
			objects[ball.x][ball.y] = 0;
			ball.vector_x *= -1;
		}
		
		//ball碰到边框反弹 
		if (((ball.x == high - 1) && (ball.y < board_width + board_y) && (ball.y >= board_y)) || (ball.x <= 0))
			ball.vector_x *= -1;
		if ((ball.y == 0) || (ball.y == width - 1))
			ball.vector_y *= -1;

		//ball移动
	
		ball.x += ball.vector_x;
		ball.y += ball.vector_y;
	}
	//防止board越界
	if (board_y < 0) board_y = 0;
	if (board_width + board_y >= width) board_y = width - 1 - board_width;
}

//受玩家的更新
void UpdataWithInput() {
	char input;
	if (_kbhit()) {
		input = _getch();
		if (input == 'a') board_y--;
		if (input == 'd') board_y++;
	}
}

//游戏结束
int game_over() {
	if (ball.x == high)
		return 0;
	else
		return 1;
}

//计分
int game_score() {
	int total_score = obj_high * width;
	int score=0, remain_object=0;
	for (i = 0; i < obj_high*width; i++)
		remain_object += *(objects[0] + i);
	score = total_score - remain_object;
	return score;
}

// 用于隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

int main()
{
	startup();
	while (game_over()) {
		UpdataWithInput();
		UpdataWithoutInput();
		HideCursor();
		show();
		printf("积分:%d\n", game_score());
	}
	printf("游戏结束!\n");
	system("pause");
	return 0;
}
