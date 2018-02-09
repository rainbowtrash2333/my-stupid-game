/*           贪吃蛇               */
/*   W A S D 移动 空格加速移动   */

/*
***canvas数据中, 大于0的为蛇身***
***每次数据刷新时, >0的数据加一, 原蛇尾数据为0*** 
*/ 

//#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<math.h>

#define high 20
#define width 30

//全局变量 
int canvas[high][width];
int head_x, head_y;
int food_x, food_y;
int tail_x, tail_y;
int i, j;
int direction;
int game_speed; //移动速度 
int speed_up;  //是否加速移动 
int game_over; //是否结束游戏 
int score; //分数

//初始化数据 
void startup() {
	head_x = high / 2;
	head_y = width / 2;
	food_x = high / 3;
	food_y = width / 3;
	speed_up = 0; //0 不加速  1 加速 
	game_over = 1; //0 结束游戏  1 不结束 
	direction=4; //开局向右移动 
	score = 0;
	//数组初始化为0
	for (i = 0; i < high; ++i) {
		for (j = 0; j < width; ++j)
			canvas[i][j] = 0;
	}
	//蛇数据为1 2 3
	for (i = 0; i < 3; ++i) {
		canvas[head_x][head_y-i] = 1+i;
	}
	//食物
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

//开始须知
void readme() {
	system("cls");
	printf("==============贪吃蛇==============\n");
	printf("===                            ===\n");
	printf("===   S W A D 移动, 空格加速   ===\n");
	printf("===                            ===\n");
	printf("=== 咬到边框及自己,则游戏结束! ===\n");
	printf("===                            ===\n");
	printf("===    made by rainbowtrash    ===\n");
	printf("===                            ===\n");
	printf("===        按任意键开始        ===\n");
	printf("===                            ===\n");
	printf("==================================\n");
	_getch();
	system("cls");
}
void finish() {
	int main(void);
	system("cls");
	printf("==============贪吃蛇==============\n");
	printf("===                            ===\n");
	printf("===          游戏结束 !        ===\n");
	printf("===                            ===\n");
	printf("===          得分: %03d         ===\n",score);
	printf("===                            ===\n");
	printf("===        是否从新开始        ===\n");
	printf("===                            ===\n");
	printf("===    输入 1 -----从新游戏    ===\n");
	printf("===    输入 2 -----结束程序    ===\n");
	printf("===                            ===\n");
	printf("==================================\n");
	printf("请输入:");
	//用字符串 
	char input[1024];
	gets_s(input);  /*gets：
					  C11标准中移除
					  C++11标准中被标记为过时，C++14标准中移除
					  用gets_s或者fgets代替*/
	if (input[0] == '1') main();
	else if(input[0]=='2'){
		system("cls");
		system("pause");
		exit(1);
	}
	else finish();
}
//打印图形 
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
	printf("得分: %03d\n", score);
	printf("made by rainbowtrash\n");
	Sleep(game_speed); //控制速度 
}

//判断移动方向 
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

//生成食物 
void produceFood() {
	srand((unsigned)time(NULL));
	int flag = 1;
	//食物是否出现在蛇身上
	//在蛇身上,则重新出现 
	while (flag) {
		food_x = rand() % high;
		food_y = rand() % width;
		if (canvas[food_x][food_y] == 0)
			flag = 0;
	}
	canvas[food_x][food_y] = -1;
}

//数据跟新 
void updata() {
	int move = move_direction(); //记录返回值 
	int max = 0;
	for (i = 0; i < high; ++i) {
		for (j = 0; j < width; ++j) {
			//寻找尾巴 
			if (canvas[i][j] > max) {
				max = canvas[i][j];
				tail_x = i;
				tail_y = j;
			}
			if (canvas[i][j] > 0) canvas[i][j]++;
		}
	}
	//用户输入时, 更改蛇头位置 
	if (move != 0) {
		if (move == 1) head_x--;
		else if (move == 2) head_x++;
		else if (move == 3) head_y--;
		else if (move == 4) head_y++;
		//跟新方向
		direction = move;
	}
	//用户无输入时, 蛇沿原方向移动 
	else if (move == 0) {
		if (direction == 1) head_x--;
		else if (direction == 2) head_x++;
		else if (direction == 3) head_y--;
		else if (direction == 4) head_y++;
	}
	//接触边框结束游戏 
	if ((head_x == -1) || (head_x == high) || (head_y == -1) || (head_y == width)) game_over = 0;
	//产生新食物  
	if (canvas[head_x][head_y] == -1) {
		produceFood();
	}
	//咬到自己
	else if (canvas[head_x][head_y] > 1) game_over = 0;
	//没吃到食物, 旧尾巴消失 
	else canvas[tail_x][tail_y] = 0;  canvas[head_x][head_y] = 1;
	//加速判断 
	if (speed_up == 0) game_speed = 20+(int)800/pow((double)max,0.4); //长度越长, 数度越快
	else {
		game_speed = 20;
		speed_up = 0;
	}
	//分数计算
	score = max - 3;
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

//main函数
int main() {
	startup();
	readme();
	while (game_over) {
		show();
		debug(0);
		updata();
	}
	finish();
	return 0;
}
