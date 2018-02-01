#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

//全局变量
int air_x, air_y;
int bullet_x, bullet_y;
int high, width;
int enemy_x, enemy_y;
int score;
int game_over;

// 用于隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//初始化数据
void starup() {
	high = 20;
	width = 30;
	air_x = high / 2;
	air_y = width / 2;
	bullet_x = bullet_y = 0;
	enemy_x = high + 1;
	score = 0;
	game_over = 0;
}

//显示画面
void show() {
	system("cls");
	int i, j;
	//打印画面
	for (i = 0; i < high; ++i) {
		for (j = 0; j < width; ++j) {
			if ((i == air_x) && (j == air_y))
				printf("*");
			else if ((i == enemy_x) && (j == enemy_y))
				printf("#");
			else if ((i == bullet_x) && (j == bullet_y))
				printf("|");
			//边框
			else {
				if (i == high - 1)
					printf("_");
				else if (j == width - 1)
					printf(" |");
				else
					printf(" ");
			}
		}
		printf("\n");
	}
	printf("击中了:%d架敌机.", score);
}

//敌机速度控制
int speed(int speed_num) {
	static int n=0;
	n++;
	if (n == speed_num) {
		n = 0;
		return 1;
	}
	return 0;
}

//玩家不控制的更新
void update_without_input() {
	//子弹上移
	if (bullet_x > -1)
		--bullet_x;
	
	//敌机判定
	if (enemy_x < high) {
		if (speed(8))
			++enemy_x;
		if ((enemy_x == bullet_x) && (enemy_y == bullet_y)) {
			enemy_x = high + 1;
			bullet_x = -1;
			score++;
		}	
	}
	else
	{
		srand(time(NULL));
		enemy_x = 0;
		enemy_y = 1 + rand() % (high - 2);
	}
	
	//飞机越界
	if (air_x > high-2)
		air_x = high-2;
	if (air_y > width-2)
		air_y = width-2;
	if (air_x < 0)
		air_x = 0;
	if (air_y < 0)
		air_y = 0;
	
	//游戏是否结束
	if ((enemy_x == air_x) && (enemy_y == air_y))
		game_over = 1;
}

//玩家控制的更新
void update_with_input() {
	char input;
	//控制
	if (_kbhit())
	{
		input = _getch();
		if (input == 'w')
			air_x--;
		if (input == 's')
			air_x++;
		if (input == 'a')
			air_y--;
		if (input == 'd')
			air_y++;
		if (input == 'f')
		{
			bullet_x = air_x - 1;
			bullet_y = air_y;
		}
	}
}

int main()
{
	starup();
	HideCursor(); // 隐藏光标

	while (game_over == 0) {
		update_with_input();
		update_without_input();
		show();
		Sleep(50);
	}
	system("cls");
	printf("游戏结束\n一共击中了%d架敌机\n",score);
	system("pause");
	return 0;
}
