#pragma once

#ifndef _HELPER_H_
#define _HELPER_H_
#include "afxwin.h"

#include <string>

#include <sstream>
#include <stdio.h>



class Helper{

public:
	//设置列表头部信息函数
	static void setCombox(CComboBox &combox);

	//画直角坐标系
	static void drawCoordinate(CClientDC &dc, int startx, int starty, int endx, int endy,int midLength);

	static void drawLine(CClientDC &dc, int **nums, int n, int len, int startx, int starty, int midLength, int endy);

	static void drawSingleLine(CClientDC &dc, int **nums, int n, int len, int startx, int starty, int midLength, int endy, int pen_num);
};


#endif // !_HELPER_H_