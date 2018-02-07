/*      һ������BIUG��������Ϸ       */
/*       made by rainbowtrash        */

//#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

#define high 25
#define width 50
#define game_speed 50  //��Ϸ�ٶȿ���

//ȫ�ֱ���
int canvas[high][width]; // '0' ->space  ; '1' ->airplane * ;'2'->bullet | ,  '3'->enemy # , '4'->hit ??;
int i, j;
int *air;
int score;
int health;

//��ʼ������
void startup() {
        for (i = 0; i < high; ++i) {
                for (j = 0; j < width; ++j)
                        canvas[i][j] = 0;
        }
        canvas[high / 2][width / 2] = 1;
        air = &canvas[high / 2][width / 2];
        score = 0;
        health = 3;
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


//��ӡ����
void show() {
        gotoxy(0, 0);
        HideCursor();
        for (i = 0; i < high+1; ++i) {
                for (j = 0; j < width+1; ++j) {
                        if (j == width) printf("|");
                        else if (i == high) printf("_");
                        else if (canvas[i][j] == 0) printf(" ");
                        else if (canvas[i][j] == 1) printf("*");
                        else if (canvas[i][j] == 2) printf("|");
                        else if (canvas[i][j] == 3) printf("#");
                        else if (canvas[i][j] == 4) printf("??");
                }
                printf("\n");
        }
        Sleep(game_speed);
        printf("����?��: %d\t��?��?: %d\n",health,score);
}

//�й��û�����ĸ���
void DataupWithInput() {
        char input;
        if (_kbhit()) {
                input = _getch();
                if (input == 's') {
                        *air = 0;
                        air = (air + width);
                        *air = 1;
                }
                else if (input == 'w') {
                        *air = 0;
                        air = (air - width);
                        *air = 1;
                }
                else if (input == 'a') {
                        *air = 0;
                        air = (air -1);
                        *air = 1;
                }
                else if (input == 'd') {
                        *air = 0;
                        air = (air + 1);
                        *air = 1;
                }
                else if (input == ' ') {
                        *(air - width) = 2;
                }
        }
}


//�����л�����
int product_anamy(int production_speed) {
        static int n=0;
        if (n < production_speed) {
                ++n;
                return 0;
        }
        else {
                srand((unsigned)time(NULL));
                //canvas[0][2] = 3;
                canvas[0][rand() % width] = 3;
                n = 0;
                return 1;
        }
}

//���û��޹ص����ݸ���
void DataupWithoutInput() {
        int new_canvas[high][width];
        for (i = 0; i < high; ++i) {
                for (j = 0; j < width; ++j) {
                         //�ڶ��˵��ӵ�
                        if ((i == 0) && (canvas[0][j] == 2)) {
                                new_canvas[0][j] = 0;
                                canvas[0][j] = 0;
                        }
                        //�ɻ�
                        else if (canvas[i][j] == 1) {
                                new_canvas[i][j] = 1;
                                canvas[i][j] = 0;
                        }
                        //ǰ���ел����ӵ�
                        //�߼�������
                        else if ((canvas[i][j] == 2) && (canvas[i - 1][j] == 3)) {
                                new_canvas[i - 1][j] = 4;
                                new_canvas[i][j] = 0;
                                canvas[i - 1][j] = 0;
                                canvas[i][j] == 0;
                                score++;
                        }
                        //ǰ��û�л����ӵ�
                        else if ((canvas[i][j] == 2) && !(canvas[i - 1][j] == 3)) {
                                new_canvas[i - 1][j] = 2;
                                new_canvas[i][j] = 0;
                                canvas[i][j] = 0;
                        }
                        //���к�ķ�����ʧ
                        else if (canvas[i][j] == 4) {
                                new_canvas[i][j] = 0;
        for (i = high - 1; i > -1; --i) {
                for (j = width - 1; j > -1; --j) {
                        //�׶˵ĵл���ʧ
                        if ((i == high - 1) && (canvas[i][j] == 3)) {
                                canvas[i][j] = 0;
                                new_canvas[i][j] = 0;
                        }
                        //�л��ƶ�
                        else if (canvas[i][j] == 3) {
                                new_canvas[i + 1][j] = 3;
                                new_canvas[i][j] = 0;
                                canvas[i][j] = 0;
                        }
                        //�л����зɻ�, ������һ
                        if ((canvas[i][j] == 3) && canvas[i + 1][j] == 1) health--;
                }
        }
        //�����µ�canvas
        for (i = 0; i < high; ++i) {
                for (j = 0; j < width; ++j) {
                        canvas[i][j] = new_canvas[i][j];
                        }
                }
        //���ʱ�����ɵл�
        srand((unsigned)time(NULL));
        product_anamy(20+rand()%20);
}

//��Ϸ����      
int game_over() {
        if (health) return 1;
        else return 0;
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
                Sleep(500);
                return 1;

        }
}

//main����
int main()
{
        startup();
        while(game_over()) {
                DataupWithInput();
                show();
                debug(0);
                DataupWithoutInput();

        }
    return 0;
}


