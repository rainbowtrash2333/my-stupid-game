//#include"stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>

#define High 480  // ��Ϸ����ߴ�
#define Width 640
#define ball_num 15
struct ball {
	int x;
	int y;
	int r;
	int speed_x ;
	int speed_y ;
}ball[ball_num];

int za;
//����Ƿ�����������ײ
//��, ����ball���+1
int check_ball(int num) {
	int j;
	for (j = 0; j < num; ++j) {

			int x2 = (ball[num].x - ball[j].x)*(ball[num].x - ball[j].x); //ˮƽ����ƽ��
			int y2 = (ball[num].y - ball[j].y)*(ball[num].y - ball[j].y); //��ֱ����ƽ��
			int r2 = (ball[num].r + ball[j].r)*(ball[num].r + ball[j].r); //�뾶�͵�ƽ��
			if ((x2 + y2 )<= r2) return j + 1; 
		
		return 0;
	}
}

int main() {
	int i;
	initgraph(Width, High);
	srand((unsigned)time(NULL));
	
	//��ʼ������
	for (i = 0; i < ball_num; ++i) {
		ball[i].r = 10 + rand() % 20;
		ball[i].speed_x = 1 + rand() % 3;
		ball[i].speed_y = 1 + rand() % 3;
		ball[i].x = ball[i].r + rand() % (Width - ball[i].r);
		ball[i].y = ball[i].r + rand() % (High - ball[i].r);
	}
	
	//����Ƿ���ײ
	for (i = 0; i < ball_num; ++i) {
		do {
			ball[i].x = ball[i].r + rand() % (Width - ball[i].r);
			ball[i].y = ball[i].r + rand() % (High - ball[i].r);
		} while (check_ball(i));
	}

	//����
	BeginBatchDraw();
	while (1) {
		for (i = 0; i < ball_num; ++i) {
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillcircle(ball[i].x, ball[i].y, ball[i].r);

			//�߿�
			if ((ball[i].x <= ball[i].r) || (ball[i].x >= Width - ball[i].r)) ball[i].speed_x = -ball[i].speed_x;
			if ((ball[i].y <= ball[i].r) || (ball[i].y >= High - ball[i].r)) ball[i].speed_y = -ball[i].speed_y;
			
			//��ײ�󷴵�
			if (check_ball(i)) {
				ball[i].speed_x = -ball[i].speed_x;
				ball[i].speed_y = -ball[i].speed_y;
				ball[check_ball(i)].speed_x = -ball[check_ball(i)-1].speed_x;
				ball[check_ball(i)-1].speed_y = -ball[check_ball(i)-1].speed_y;
			}

			//�ƶ�
			ball[i].x += ball[i].speed_x;
			ball[i].y += ball[i].speed_y;
			
			//����
			setcolor(YELLOW);
			setfillcolor(GREEN);
			fillcircle(ball[i].x, ball[i].y, ball[i].r);
			
			FlushBatchDraw();
			Sleep(1);  //��ʱ
		}
	}
	EndBatchDraw();
	_getch();
	closegraph();
	return 0;
}
