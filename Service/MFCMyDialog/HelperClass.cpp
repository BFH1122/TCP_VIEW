
#include "Helper.h"


//实现静态方法
void Helper::setCombox(CComboBox &combox) {
	char *items[5];// = new char[6];
	items[0] = "1";
	items[1] = "2";
	items[2] = "3";
	items[3] = "4";
	items[4] = "5";
	for (int i = 0; i < 5; i++) {
		combox.AddString(items[i]);
	}
	combox.SetCurSel(0);
}

void Helper::drawCoordinate(CClientDC &dc,int startx,int starty,int endx,int endy,int midLength) {

	//黑色画笔
	CPen pen(PS_SOLID, 1.5, RGB(0, 0, 0));
	CPen *oldPen = dc.SelectObject(&pen);
	//注释
	dc.TextOutA(startx - 10, starty - 10, "10");
	dc.TextOutA(startx - 10, endy, "-10");
	dc.TextOutA(startx - 10, (starty + endy) / 2, "0");
	//刻度
	int x = starty;
	int m_l = (endy - starty) / 20;
	for (int i = 1; i <= 19; i++) {
		x = x + m_l;
		dc.MoveTo(startx, x);
		if (i == 5 || i == 15) {
			dc.LineTo(startx + 8, x);
		}
		else {
			dc.LineTo(startx + 5, x);
		}
	}
	//坐标轴
	dc.MoveTo(startx, starty);
	dc.LineTo(endx, endy);
	dc.MoveTo(startx, (endy + starty) / 2);
	dc.LineTo(midLength, (endy + starty) / 2);
	dc.SelectObject(oldPen);

}

void Helper::drawSingleLine(CClientDC &dc, int **nums, int n, int len, int startx, int starty, int midLength, int endy,int pen_num) {


	//初始化画笔的颜色
	
	CPen * pens[5] = {
		new CPen(PS_SOLID, 1, RGB(120, 0, 0)),
		new CPen(PS_SOLID, 1, RGB(10, 255, 0)),
		new CPen(PS_SOLID, 1, RGB(23, 0, 255)),
		new CPen(PS_SOLID, 1, RGB(125, 125, 125)),
		new CPen(PS_SOLID, 1, RGB(255, 200, 210))
	};

	// PS_SOLID, 1, RGB(255, 0, 0));
	int x, y;
	//对于每一组数据
	for (int i = 0; i < n; i++) {
		//访问其中的每一个数据点。
		y = (starty + endy) / 2 - (nums[i][0] * (endy - starty) / 20);  //第一个点的坐标
		x = midLength / len + startx; //横向的单位长度
		CPen *oldPen = dc.SelectObject(pens[pen_num]);

		for (int j = 1; j < len; j++) {
			dc.MoveTo(x, y);
			y = (starty + endy) / 2 - (nums[i][j] * (endy - starty) / 20);
			x = startx + midLength / len * (j + 1);
			dc.LineTo(x, y);
			Sleep(200);
		}
		dc.SelectObject(oldPen);
	}
}

void Helper::drawLine(CClientDC &dc, int **nums, int n, int len,int startx,int starty,int midLength,int endy) {

	//初始化画笔的颜色
	// PS_SOLID, 1, RGB(255, 0, 0));
	CPen * pens[5] = {
		new CPen(PS_SOLID, 1, RGB(120, 0, 0)),
		new CPen(PS_SOLID, 1, RGB(10, 255, 0)),
		new CPen(PS_SOLID, 1, RGB(23, 0, 255)),
		new CPen(PS_SOLID, 1, RGB(125, 125, 125)),
		new CPen(PS_SOLID, 1, RGB(255, 200, 210))
	};
	int x, y;
	//对于每一组数据
	for (int i = 0; i < n; i++) {
		//访问其中的每一个数据点。
		y = (starty + endy) / 2 - (nums[i][0] * (endy - starty) / 20);  //第一个点的坐标
		x = midLength / len + startx; //横向的单位长度
		CPen *oldPen = dc.SelectObject(pens[i]);

		for (int j = 1; j < len; j++) {
			dc.MoveTo(x, y);
			y = (starty + endy) / 2 - (nums[i][j] * (endy - starty) / 20);
			x = startx + midLength / len * (j + 1);
			dc.LineTo(x, y);
		}
		dc.SelectObject(oldPen);
	}
}
