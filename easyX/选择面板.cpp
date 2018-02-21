// 鼠标交互.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <graphics.h>
#include <windows.h>
#include<stdlib.h>
#define width 640 //宽
#define high 480 //高

//全局变量
struct bar_position {
	int Lx;
	int Ly;
	int Rx;
	int Ry;
};
struct bar_position background, YesButton, NoButton;
int flag;
//初始化数据
void startup() {
	background.Lx = width * 0.2;
	background.Ly = high * 0.15;
	background.Rx = width * 0.8;
	background.Ry = high * 0.7;
	YesButton.Lx = background.Rx*0.34;
	YesButton.Ly = NoButton.Ly = background.Ry*0.8;
	YesButton.Ry = NoButton.Ry = background.Ry*0.9;
	YesButton.Rx = YesButton.Lx + 0.2*background.Rx;
	NoButton.Lx = background.Rx*0.7;
	NoButton.Rx = background.Rx*0.9;
	YesButton.Lx = background.Rx*0.34;
	YesButton.Ly = NoButton.Ly = background.Ry*0.8;
	YesButton.Ry = NoButton.Ry = background.Ry*0.9;
	YesButton.Rx = YesButton.Lx + 0.2*background.Rx;
	NoButton.Lx = background.Rx*0.7;
	NoButton.Rx = background.Rx*0.9;
	flag = 1;
}

//暂时这样
void showYES() {
	setbkcolor(BLACK);
	cleardevice();
	setfillcolor(GREEN);
	ellipse(40, 60, 79, 80);
	flag = 0;
}
void showNO() {
	setbkcolor(BLACK);
	cleardevice();
	bar(12, 34, 45, 67);
	flag = 0;
}
//画面
void Show() {
	setfillcolor(GREEN);
	fillroundrect(background.Lx, background.Ly, background.Rx, background.Ry, 20, 20);

	MOUSEMSG m;
	m = GetMouseMsg();
	if ((m.x > YesButton.Lx) && (m.x < YesButton.Rx) && (m.y > YesButton.Ly) && (m.y < YesButton.Ry)) {
		setfillcolor(YELLOW);
		if (m.uMsg == WM_LBUTTONUP)
			flag = 2;
	}
	else setfillcolor(BLUE);
	bar(YesButton.Lx, YesButton.Ly, YesButton.Rx, YesButton.Ry);

	if ((m.x > NoButton.Lx) && (m.x < NoButton.Rx) && (m.y < NoButton.Ry) && (m.y > NoButton.Ly)) {
		setfillcolor(YELLOW);
		if (m.uMsg == WM_LBUTTONUP)
			flag = 3;
	}
	else setfillcolor(RED);
	bar(NoButton.Lx, NoButton.Ly, NoButton.Rx, NoButton.Ry);

	RECT r = { background.Lx,background.Ly,background.Rx,background.Ry };
	drawtext(_T("Do you want to do it?"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT yes = { YesButton.Lx, YesButton.Ly,YesButton.Rx,YesButton.Ry };
	drawtext(_T("yes"), &yes, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT no = { NoButton.Lx, NoButton.Ly,NoButton.Rx,NoButton.Ry };
	drawtext(_T("no"), &no, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	switch (flag) {
	case 2:
		showYES();
		break;
	case 3:
		showNO();
		break;
	}
	FlushBatchDraw();
}

int main()
{
	initgraph(640, 480);
	startup();
	BeginBatchDraw();
	while (flag) {
		Show();
	}
	EndBatchDraw();
	system("pause");
	return 0;
}


