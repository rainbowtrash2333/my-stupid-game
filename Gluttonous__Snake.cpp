/*           ̰����               */
/*   W A S D �ƶ� �ո�����ƶ�   */

/*
***canvas������, ����0��Ϊ����***
***ÿ������ˢ��ʱ, >0�����ݼ�һ, ԭ��β����Ϊ0*** 
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

//ȫ�ֱ��� 
int canvas[high][width];
int head_x, head_y;
int food_x, food_y;
int tail_x, tail_y;
int i, j;
int direction;
int game_speed; //�ƶ��ٶ� 
int speed_up;  //�Ƿ�����ƶ� 
int game_over; //�Ƿ������Ϸ 
int score; //����

//��ʼ������ 
void startup() {
	head_x = high / 2;
	head_y = width / 2;
	food_x = high / 3;
	food_y = width / 3;
	speed_up = 0; //0 ������  1 ���� 
	game_over = 1; //0 ������Ϸ  1 ������ 
	direction=4; //���������ƶ� 
	score = 0;
	//�����ʼ��Ϊ0
	for (i = 0; i < high; ++i) {
		for (j = 0; j < width; ++j)
			canvas[i][j] = 0;
	}
	//������Ϊ1 2 3
	for (i = 0; i < 3; ++i) {
		canvas[head_x][head_y-i] = 1+i;
	}
	//ʳ��
	canvas[food_x][food_y] = -1;
}

//����ƶ���( x, y ) 
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

// ���ع�� 
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//��ʼ��֪
void readme() {
	system("cls");
	printf("==============̰����==============\n");
	printf("===                            ===\n");
	printf("===   S W A D �ƶ�, �ո����   ===\n");
	printf("===                            ===\n");
	printf("=== ҧ���߿��Լ�,����Ϸ����! ===\n");
	printf("===                            ===\n");
	printf("===    made by rainbowtrash    ===\n");
	printf("===                            ===\n");
	printf("===        ���������ʼ        ===\n");
	printf("===                            ===\n");
	printf("==================================\n");
	_getch();
	system("cls");
}
void finish() {
	int main(void);
	system("cls");
	printf("==============̰����==============\n");
	printf("===                            ===\n");
	printf("===          ��Ϸ���� !        ===\n");
	printf("===                            ===\n");
	printf("===          �÷�: %03d         ===\n",score);
	printf("===                            ===\n");
	printf("===        �Ƿ���¿�ʼ        ===\n");
	printf("===                            ===\n");
	printf("===    ���� 1 -----������Ϸ    ===\n");
	printf("===    ���� 2 -----��������    ===\n");
	printf("===                            ===\n");
	printf("==================================\n");
	printf("������:");
	//���ַ��� 
	char input[1024];
	gets_s(input);  /*gets��
					  C11��׼���Ƴ�
					  C++11��׼�б����Ϊ��ʱ��C++14��׼���Ƴ�
					  ��gets_s����fgets����*/
	if (input[0] == '1') main();
	else if(input[0]=='2'){
		system("cls");
		system("pause");
		exit(1);
	}
	else finish();
}
//��ӡͼ�� 
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
	printf("�÷�: %03d\n", score);
	printf("made by rainbowtrash\n");
	Sleep(game_speed); //�����ٶ� 
}

//�ж��ƶ����� 
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

//����ʳ�� 
void produceFood() {
	srand((unsigned)time(NULL));
	int flag = 1;
	//ʳ���Ƿ������������
	//��������,�����³��� 
	while (flag) {
		food_x = rand() % high;
		food_y = rand() % width;
		if (canvas[food_x][food_y] == 0)
			flag = 0;
	}
	canvas[food_x][food_y] = -1;
}

//���ݸ��� 
void updata() {
	int move = move_direction(); //��¼����ֵ 
	int max = 0;
	for (i = 0; i < high; ++i) {
		for (j = 0; j < width; ++j) {
			//Ѱ��β�� 
			if (canvas[i][j] > max) {
				max = canvas[i][j];
				tail_x = i;
				tail_y = j;
			}
			if (canvas[i][j] > 0) canvas[i][j]++;
		}
	}
	//�û�����ʱ, ������ͷλ�� 
	if (move != 0) {
		if (move == 1) head_x--;
		else if (move == 2) head_x++;
		else if (move == 3) head_y--;
		else if (move == 4) head_y++;
		//���·���
		direction = move;
	}
	//�û�������ʱ, ����ԭ�����ƶ� 
	else if (move == 0) {
		if (direction == 1) head_x--;
		else if (direction == 2) head_x++;
		else if (direction == 3) head_y--;
		else if (direction == 4) head_y++;
	}
	//�Ӵ��߿������Ϸ 
	if ((head_x == -1) || (head_x == high) || (head_y == -1) || (head_y == width)) game_over = 0;
	//������ʳ��  
	if (canvas[head_x][head_y] == -1) {
		produceFood();
	}
	//ҧ���Լ�
	else if (canvas[head_x][head_y] > 1) game_over = 0;
	//û�Ե�ʳ��, ��β����ʧ 
	else canvas[tail_x][tail_y] = 0;  canvas[head_x][head_y] = 1;
	//�����ж� 
	if (speed_up == 0) game_speed = 20+(int)800/pow((double)max,0.4); //����Խ��, ����Խ��
	else {
		game_speed = 20;
		speed_up = 0;
	}
	//��������
	score = max - 3;
}

//debug����, ��ӡcanvas����������
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

//main����
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
