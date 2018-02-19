//实时钟表

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <TCHAR.H>
#define high 550
#define width 640
#define PI 3.141592653
int second, minute, hour;
int center_x, center_y;//钟表中心
int second_len, minute_len, hour_len;//指针长度
int second_x, second_y;////////////////////////
int minute_x, minute_y;/////指针端点坐标//////
int hour_x, hour_y;//////////////////////////
double secondAngle, minuteAngle, hourAngle;//指针旋转角度
SYSTEMTIME ti;

//选择模式
//模式1: 实时显示
//模式2: 秒表
int startup_option(char flag) {
	if (flag == '1') {
		secondAngle = ti.wSecond * 2 * PI / 60;
		minuteAngle = ti.wMinute * 2 * PI / 60;
		hourAngle = ti.wHour * 2 * PI / 24;
		second = ti.wSecond;
		minute = ti.wMinute;
		hour = ti.wHour;
		return 1;
	}
	else if (flag == '2') {
		secondAngle = minuteAngle = minuteAngle = 0;
		second = minute = hour = 0;
		return 2;
	}
	else return 0;
}
char begin() {
	system("cls");
	char input;
	printf("===============时钟===============\n");
	printf("===                            ===\n");
	printf("===      输入1: 实时显示       ===\n");
	printf("===      输入2:   秒表         ===\n");
	printf("===                            ===\n");
	printf("===    made by rainbowtrash    ===\n");
	printf("===                            ===\n");
	printf("===           请输入           ===\n");
	printf("===                            ===\n");
	printf("==================================\n");
	input = _getch();
	system("cls");
	if ((input == '1') || input == '2')
		return input;
	begin();
	return 0;
}

void startup(){
	center_x = width / 2;
	center_y = high / 2;
	second_len = width / 3;
	minute_len = width / 5;
	hour_len = width / 6;
	GetLocalTime(&ti);
	startup_option(begin());
	second_y = center_y - second_len * cos(secondAngle);
	minute_y = center_y - minute_len * cos(minuteAngle);
	hour_y = center_y - hour_len * cos(hourAngle);
	second_x = (int)(center_x + second_len * sin(secondAngle));
	minute_x = (int)(center_x + minute_len * sin(minuteAngle));
	hour_x = (int)(center_x + hour_len * sin(hourAngle));
	initgraph(width, high);
}

void update() {
	//指针终点坐标
	//利用三角函数计算
	secondAngle += 2 * PI / 60;
	second++;
	second_y = center_y - second_len * cos(secondAngle);
	minute_y = center_y - minute_len * cos(minuteAngle);
	hour_y = center_y - hour_len * cos(hourAngle);
	second_x = (int)(center_x + second_len * sin(secondAngle));
	minute_x = (int)(center_x + minute_len * sin(minuteAngle));
	hour_x = (int)(center_x + hour_len * sin(hourAngle));
	

	//秒表记录
	if (second == 60) {
		minute++;
		minuteAngle+= 2 * PI / 60;
		second = 0;
		secondAngle = 0;
	}
	if (minute == 60) {
		hour++;
		hourAngle+= 2 * PI / 60;
		minute = 0;
		minuteAngle = 0;
	}
}

void show() {	
	//画表盘
	int R = second_len + 25;
	setlinestyle(PS_SOLID, 1);
	setcolor(WHITE);
	circle(center_x, center_y, R);
	//画刻度
	int x, y, i,r;
	r = R - 10;
	for (i = 0; i < 60; ++i) {
		x = center_x + r * sin(2 * PI * i / 60);
		y = center_y - r * cos(2 * PI * i / 60);
		if (i % 15 == 0)
			bar(x - 5, y - 5, x + 5, y + 5);
		else if (i % 5 == 0)
			circle(x, y, 4);
		else
			putpixel(x, y, WHITE);
	}
	//写字
	TCHAR s[sizeof("我的时钟")];
	swprintf_s(s, _T("%s"), L"我的时钟");
	outtextxy((int)center_x - 25, center_y + width / 6, s);
	//显示时间
	TCHAR t[sizeof("01:01:01")];
	swprintf_s(t, _T("%02d:%02d:%02d"), hour,minute,second);
	outtextxy((int)center_x - 25, center_y + width / 5, t);
	
	//画秒钟
	setlinestyle(PS_SOLID, 2);//实线,长度为两像素
	setcolor(WHITE);
	line(center_x, center_y, second_x,second_y);
	//画分针
	setlinestyle(PS_SOLID, 4);//实线,长度为两像素
	setcolor(BLUE);
	line(center_x, center_y, minute_x, minute_y);
	//画时钟
	setlinestyle(PS_SOLID, 6);//实线,长度为两像素
	setcolor(RED);
	line(center_x, center_y, hour_x, hour_y);
	Sleep(1000);
	
	//隐藏前一个指针的残影
	setcolor(BLACK);
	line(center_x, center_y, second_x, second_y);
	line(center_x, center_y, minute_x, minute_y);
	line(center_x, center_y, hour_x, hour_y);
}

int main()
{
	startup();
	while (1) {
		show();
		update();
	}
	closegraph();
    return 0;
}
