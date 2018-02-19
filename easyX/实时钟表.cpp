//ʵʱ�ӱ�

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
int center_x, center_y;//�ӱ�����
int second_len, minute_len, hour_len;//ָ�볤��
int second_x, second_y;////////////////////////
int minute_x, minute_y;/////ָ��˵�����//////
int hour_x, hour_y;//////////////////////////
double secondAngle, minuteAngle, hourAngle;//ָ����ת�Ƕ�
SYSTEMTIME ti;

//ѡ��ģʽ
//ģʽ1: ʵʱ��ʾ
//ģʽ2: ���
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
	printf("===============ʱ��===============\n");
	printf("===                            ===\n");
	printf("===      ����1: ʵʱ��ʾ       ===\n");
	printf("===      ����2:   ���         ===\n");
	printf("===                            ===\n");
	printf("===    made by rainbowtrash    ===\n");
	printf("===                            ===\n");
	printf("===           ������           ===\n");
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
	//ָ���յ�����
	//�������Ǻ�������
	secondAngle += 2 * PI / 60;
	second++;
	second_y = center_y - second_len * cos(secondAngle);
	minute_y = center_y - minute_len * cos(minuteAngle);
	hour_y = center_y - hour_len * cos(hourAngle);
	second_x = (int)(center_x + second_len * sin(secondAngle));
	minute_x = (int)(center_x + minute_len * sin(minuteAngle));
	hour_x = (int)(center_x + hour_len * sin(hourAngle));
	

	//����¼
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
	//������
	int R = second_len + 25;
	setlinestyle(PS_SOLID, 1);
	setcolor(WHITE);
	circle(center_x, center_y, R);
	//���̶�
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
	//д��
	TCHAR s[sizeof("�ҵ�ʱ��")];
	swprintf_s(s, _T("%s"), L"�ҵ�ʱ��");
	outtextxy((int)center_x - 25, center_y + width / 6, s);
	//��ʾʱ��
	TCHAR t[sizeof("01:01:01")];
	swprintf_s(t, _T("%02d:%02d:%02d"), hour,minute,second);
	outtextxy((int)center_x - 25, center_y + width / 5, t);
	
	//������
	setlinestyle(PS_SOLID, 2);//ʵ��,����Ϊ������
	setcolor(WHITE);
	line(center_x, center_y, second_x,second_y);
	//������
	setlinestyle(PS_SOLID, 4);//ʵ��,����Ϊ������
	setcolor(BLUE);
	line(center_x, center_y, minute_x, minute_y);
	//��ʱ��
	setlinestyle(PS_SOLID, 6);//ʵ��,����Ϊ������
	setcolor(RED);
	line(center_x, center_y, hour_x, hour_y);
	Sleep(1000);
	
	//����ǰһ��ָ��Ĳ�Ӱ
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
