/*      一个满满BIUG的垃圾游戏       */
/*       made by rainbowtrash        */

//#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

#define high 25
#define width 50
#define game_speed 50  //游戏速度控制

//全局变量
int canvas[high][width]; // '0' ->space  ; '1' ->airplane * ;'2'->bullet | ,  '3'->enemy # , '4'->hit ??;
int i, j;
int *air;
int score;
int health;

//初始化数据
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


//打印画面
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
        printf("éú?ü: %d\tμ?·?: %d\n",health,score);
}

//有关用户输入的更新
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


//产生敌机函数
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

//于用户无关的数据更新
void DataupWithoutInput() {
        int new_canvas[high][width];
        for (i = 0; i < high; ++i) {
                for (j = 0; j < width; ++j) {
                         //在顶端的子弹
                        if ((i == 0) && (canvas[0][j] == 2)) {
                                new_canvas[0][j] = 0;
                                canvas[0][j] = 0;
                        }
                        //飞机
                        else if (canvas[i][j] == 1) {
                                new_canvas[i][j] = 1;
                                canvas[i][j] = 0;
                        }
                        //前方有敌机的子弹
                        //逻辑有问题
                        else if ((canvas[i][j] == 2) && (canvas[i - 1][j] == 3)) {
                                new_canvas[i - 1][j] = 4;
                                new_canvas[i][j] = 0;
                                canvas[i - 1][j] = 0;
                                canvas[i][j] == 0;
                                score++;
                        }
                        //前方没敌机的子弹
                        else if ((canvas[i][j] == 2) && !(canvas[i - 1][j] == 3)) {
                                new_canvas[i - 1][j] = 2;
                                new_canvas[i][j] = 0;
                                canvas[i][j] = 0;
                        }
                        //击中后的废墟消失
                        else if (canvas[i][j] == 4) {
                                new_canvas[i][j] = 0;
        for (i = high - 1; i > -1; --i) {
                for (j = width - 1; j > -1; --j) {
                        //底端的敌机消失
                        if ((i == high - 1) && (canvas[i][j] == 3)) {
                                canvas[i][j] = 0;
                                new_canvas[i][j] = 0;
                        }
                        //敌机移动
                        else if (canvas[i][j] == 3) {
                                new_canvas[i + 1][j] = 3;
                                new_canvas[i][j] = 0;
                                canvas[i][j] = 0;
                        }
                        //敌机集中飞机, 生命减一
                        if ((canvas[i][j] == 3) && canvas[i + 1][j] == 1) health--;
                }
        }
        //生成新的canvas
        for (i = 0; i < high; ++i) {
                for (j = 0; j < width; ++j) {
                        canvas[i][j] = new_canvas[i][j];
                        }
                }
        //随机时间生成敌机
        srand((unsigned)time(NULL));
        product_anamy(20+rand()%20);
}

//游戏结束      
int game_over() {
        if (health) return 1;
        else return 0;
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
                Sleep(500);
                return 1;

        }
}

//main函数
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


