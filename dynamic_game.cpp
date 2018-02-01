/***
                   *������Ϸ*
*��������ʵ�ֶ�ÿһ��cell���������Դ���(1 or 0)*
***/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define high 25
#define width 50

//ȫ�ֱ���
int cells[high+2][width+2];
int i, j;

//���ݳ�ʼ��
void startup() {
	srand((unsigned)time(NULL));
	//��Χ���ֵ��Ϊ0
	for (i = -1; i < high+1; ++i)
		for (j = -1; j < width + 1; ++j) {
			cells[i][j] = rand() % 2;
			if ((i == -1) || (i == high) || (j == -1) || (j == width)) cells[i][j] = 0;
		}
}

void show(){
	system("cls");
	for (i = 0; i < high; ++i) {
		for (j = 0; j < width; ++j) {
			if (cells[i][j] == 1) printf("*");
			else printf(" ");
		}
		printf("\n");
	}
	Sleep(1000);
}

void without_input_update() {
	int new_cells[high][width];
	int neighbor;
	for (i = 0; i < high; ++i) {
		for (j = 0; j < width; ++j) {
			//cell��Χ��ֵ��ӵõ�����Χ��cell��
			neighbor = cells[i - 1][j - 1] + cells[i - 1][j] + cells[i - 1][j + 1] + cells[i][j - 1] + cells[i][j + 1] + cells[i + 1][j - 1] + cells[i + 1][j] + cells[i + 1][j + 1];
			if (neighbor == 3) new_cells[i][j] = 1;
			else if (neighbor == 2) new_cells[i][j] = cells[i][j];
			else new_cells[i][j] = 0;
			cells[i][j] = new_cells[i][j];
		}
	}
}

void with_input_update() {

}

int game_over() {
	return 1;
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
	while (game_over) {
		HideCursor();
		with_input_update();
		without_input_update();
		show();

	}

    return 0;
}
