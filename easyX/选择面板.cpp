/* 
 *****学习鼠标交互及图形绘画*****
       ******使用VS2017***** 
                                 */

#include <graphics.h>
#include <windows.h>
#define width 640 //宽
#define high 480 //高

//全局变量
struct bar_position {
	double Lx;
	double Ly;
	double Rx;
	double Ry;
};
struct bar_position background, YesButton, NoButton;
int flag;
//初始化数据
void startup() {
	initgraph(640, 480);
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

//YES界面
void showYES() {
	//清空界面(红色)
	setbkcolor(RED);
	cleardevice();
	setfillcolor(YELLOW);
	//画三角形
	double x, y, r;
	x = width / 2;
	y = high / 2;
	r = high / 4;
	POINT pts[] = { {x,y - r},{x - 1.732*r,y + r * 0.5},{x + 1.732*r,y + r * 0.5} };
	fillpolygon(pts, 3);
	//写字
	TCHAR s[] = _T("ERROR! ");
	outtextxy(x - 20, y, s);
	flag = 0;
}
//NO界面
void showNO() {
	//清空界面(黑色)
	setbkcolor(BLACK);
	cleardevice();
	setfillcolor(GREEN);
	//画矩形
	double x, y, r;
	x = width / 2;
	y = high / 2;
	r = high / 4;
	bar(x - r, y - 0.7*r, x + r, y + 0.7*r);
	//写字
	RECT no = { x - r,y - 0.7*r,x + r,y + 0.7*r };
	drawtext(_T("DO NOTHING"), &no, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	flag = 0;
}
//画选择界面
void Show() {
	//画圆角矩形
	setfillcolor(GREEN);
	fillroundrect(background.Lx, background.Ly, background.Rx, background.Ry, 20, 20);
	//鼠标控制
	MOUSEMSG m;
	m = GetMouseMsg();
	if ((m.x > YesButton.Lx) && (m.x < YesButton.Rx) && (m.y > YesButton.Ly) && (m.y < YesButton.Ry)) {
		//鼠标碰到变色
		setfillcolor(YELLOW);
		//左键单击跳转YES界面
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
	//写字
	RECT r = { background.Lx,background.Ly,background.Rx,background.Ry };
	drawtext(_T("Do you want to do it?"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT yes = { YesButton.Lx, YesButton.Ly,YesButton.Rx,YesButton.Ry };
	drawtext(_T("yes"), &yes, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT no = { NoButton.Lx, NoButton.Ly,NoButton.Rx,NoButton.Ry };
	drawtext(_T("no"), &no, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//跳转页面
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
	startup();
	BeginBatchDraw();
	while (flag) {
		Show();
	}
	EndBatchDraw();
	//结束
	Sleep(1500);
	closegraph();
	return 0;
}


