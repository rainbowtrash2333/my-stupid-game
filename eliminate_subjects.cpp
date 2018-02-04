/*
    ***������***
***A D ���Ƶ����ƶ�*** 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//ȫ�ֱ���
#define high 20
#define width 30
#define obj_high 3
int i, j;
int objects[obj_high][width];
int board_y,board_width;
//���λ�ü�����
typedef struct Ball {
	int x;
	int y;
	int vector_x;
	int vector_y;
}Ball;
Ball ball;

//���ݳ�ʼ��
void startup() {
	ball.x = high / 2;
	ball.y = width / 2 ;
	//��X Y ����Ϊ��
	ball.vector_x = 1;
	ball.vector_y = 1;
	board_width = 5;
	board_y = (width - board_width) / 2 ;
	//object��ʼ��Ϊ1
	for (i = 0; i < obj_high*width; i++)
		*(objects[0]+i) = 1;
}

//����ƶ���(x,y)λ��
void gotoxy(int x, int y)  
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//��ӡͼ��
void show() {
//	system("cls");
	gotoxy(0, 0);
	for (i = 0; i < high+1; i++) {
		for (j = 0; j < width+1; j++) {
			
			//��ӡball
			if ((i == ball.x)&& (j == ball.y)) 
            	printf("@");
			
			//��ӡ�߿�
			else if (i == high) printf("_");
			else if (j == width) printf("|");
			
			//��ӡobjects
			else if ((i < obj_high)&& (objects[i][j]))
					printf("*");

			//��ӡboard
			else if ((i == high-1)&& (j < board_width + board_y) && (j >= board_y))
					printf("-");
			else
				printf(" ");
		}
		printf("\n");
	}
	Sleep(50);
}

//ball�ƶ��ٶȿ���
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

//������ҵĸ���
void UpdataWithoutInput() {
	
	if (BallSpeedControl(3)) {
	
		//����object �ͷ���
		if ((ball.x < obj_high)&&(objects[ball.x][ball.y])) {
			objects[ball.x][ball.y] = 0;
			ball.vector_x *= -1;
		}
		
		//ball�����߿򷴵� 
		if (((ball.x == high - 1) && (ball.y < board_width + board_y) && (ball.y >= board_y)) || (ball.x <= 0))
			ball.vector_x *= -1;
		if ((ball.y == 0) || (ball.y == width - 1))
			ball.vector_y *= -1;

		//ball�ƶ�
	
		ball.x += ball.vector_x;
		ball.y += ball.vector_y;
	}
	//��ֹboardԽ��
	if (board_y < 0) board_y = 0;
	if (board_width + board_y >= width) board_y = width - 1 - board_width;
}

//����ҵĸ���
void UpdataWithInput() {
	char input;
	if (_kbhit()) {
		input = _getch();
		if (input == 'a') board_y--;
		if (input == 'd') board_y++;
	}
}

//��Ϸ����
int game_over() {
	if (ball.x == high)
		return 0;
	else
		return 1;
}

//�Ʒ�
int game_score() {
	int total_score = obj_high * width;
	int score=0, remain_object=0;
	for (i = 0; i < obj_high*width; i++)
		remain_object += *(objects[0] + i);
	score = total_score - remain_object;
	return score;
}

// �������ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // �ڶ���ֵΪ0��ʾ���ع��
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
		printf("����:%d\n", game_score());
	}
	printf("��Ϸ����!\n");
	system("pause");
	return 0;
}
