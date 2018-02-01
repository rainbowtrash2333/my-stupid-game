/*
***flappy bird 游戏, 然而我忘记整么玩的了,就乱搞吧***
***           swad控制鸟, 记分没弄,就酱          ***
*/

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

//全局变量
int high, width;
int score;
struct bird {
	int x;
	int y;
	int heath;
	int gravity;
}bird;
struct barrier {
	int y;
	int gap_high;
	int gap_x;
}barr[4];

//初始化数据
void starup()
{
	high = 15;
	width = 40;
	score = 0;
	bird.x = high / 2;
	bird.y = width / 4;
	bird.heath = 3;
	bird.gravity = 6;
	barr[0].y = width/2;
	barr[1].y = width/4 *3;
	barr[2].y = width;
	barr[3].y = width/4 *5;
	
	//随机生成障碍缺口参数
	int i;
	srand((unsigned)time(NULL));
	for (i = 0; i<4; ++i) {
		barr[i].gap_high = 2 + rand() % 2;
		barr[i].gap_x = rand() % (high - barr[i].gap_high);
	}
}

//图形显示
void show() {
	system("cls");
	int i, j;
	for (i = 0; i < high + 1; ++i) {
		for (j = 0; j < width + 1; ++j) {
			if ((i == bird.x) && (j == bird.y)) printf("@");
			else if ((!((i >= barr[0].gap_x) && (i <= barr[0].gap_x + barr[0].gap_high)) && (j == barr[0].y)) || (!((i >= barr[1].gap_x) && (i <= barr[1].gap_x + barr[1].gap_high)) && (j == barr[1].y)) || (!((i >= barr[2].gap_x) && (i <= barr[2].gap_x + barr[2].gap_high)) && (j == barr[2].y))|| (!((i >= barr[3].gap_x) && (i <= barr[3].gap_x + barr[3].gap_high)) && (j == barr[3].y)))
				printf("*");
			else printf(" ");
		}
		printf("\n");
	}
	printf("共%d分\t还有%d条生命\n", score, bird.heath);
	Sleep(50);
}

//玩家控制部分
void update_without_input() {
	char input;
	if (_kbhit()) {
		input = _getch();
		if (input == 'a') bird.y --;
		if (input == 'd') bird.y ++;
		if (input == 'w') bird.x --;
		if (input == 's') bird.x ++;
	}
}

//速度控制
int speed_gravity(int n) {
	static int i = 0;
	++i;
	if (i > n) {
		i = 0;
		return 1;
	}
	return 0;
}
int speed(int n) {
	static int i = 0;
	++i;
	if (i > n) {
		i = 0;
		return 1;
	}
	return 0;
}

//玩家不能控制部分
void update_with_input() {
	
	//鸟下坠
	if (speed_gravity(bird.gravity)) bird.x++;
	
	//障碍左移
	if (speed(7)) {
		int i;
		for (i = 0; i < 4; ++i) barr[i].y--;		
	}

	//循环生成障碍
	if (barr[0].y == -1) {
		struct barrier temp;
		barr[0].y = width/4 *5;
		barr[0].gap_high = 2 + rand() % 2;
		barr[0].gap_x = rand() % (high - barr[0].gap_high);
		temp = barr[0];
		barr[0] = barr[1];
		barr[1] = barr[2];
		barr[2] = barr[3];
		barr[3] = temp;
	}

	//鸟与障碍碰撞
	int i;
	for (i = 0; i < 4; ++i) {
		if (bird.y == barr[i].y) {
			if (!((bird.x >= barr[i].gap_x) && (bird.x <= barr[i].gap_x + barr[i].gap_high))) {
				--bird.heath;
				Sleep(500);
				bird.x = barr[i].gap_x + 1;
			}			
		}
	}
}

//游戏结束判定
int game_over() {
	if (bird.heath == 0) return 0;
	else return 1;
}

// 用于隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

int main()
{
	starup();
	HideCursor(); // 隐藏光标
	while (game_over()) {
		update_with_input();
		update_without_input();
		show();
	}
	printf("游戏结束!\n");
	system("pause");
	return 0;
}
