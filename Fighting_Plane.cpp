#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

//ȫ�ֱ���
int air_x, air_y;
int bullet_x, bullet_y;
int high, width;
int enemy_x, enemy_y;
int score;
int game_over;

// �������ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // �ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//��ʼ������
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

//��ʾ����
void show() {
	system("cls");
	int i, j;
	//��ӡ����
	for (i = 0; i < high; ++i) {
		for (j = 0; j < width; ++j) {
			if ((i == air_x) && (j == air_y))
				printf("*");
			else if ((i == enemy_x) && (j == enemy_y))
				printf("#");
			else if ((i == bullet_x) && (j == bullet_y))
				printf("|");
			//�߿�
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
	printf("������:%d�ܵл�.", score);
}

//�л��ٶȿ���
int speed(int speed_num) {
	static int n=0;
	n++;
	if (n == speed_num) {
		n = 0;
		return 1;
	}
	return 0;
}

//��Ҳ����Ƶĸ���
void update_without_input() {
	//�ӵ�����
	if (bullet_x > -1)
		--bullet_x;
	
	//�л��ж�
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
	
	//�ɻ�Խ��
	if (air_x > high-2)
		air_x = high-2;
	if (air_y > width-2)
		air_y = width-2;
	if (air_x < 0)
		air_x = 0;
	if (air_y < 0)
		air_y = 0;
	
	//��Ϸ�Ƿ����
	if ((enemy_x == air_x) && (enemy_y == air_y))
		game_over = 1;
}

//��ҿ��Ƶĸ���
void update_with_input() {
	char input;
	//����
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
	HideCursor(); // ���ع��

	while (game_over == 0) {
		update_with_input();
		update_without_input();
		show();
		Sleep(50);
	}
	system("cls");
	printf("��Ϸ����\nһ��������%d�ܵл�\n",score);
	system("pause");
	return 0;
}
