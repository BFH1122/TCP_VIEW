#pragma once

#ifndef _HELPER_H_
#define _HELPER_H_
#include "afxwin.h"

#include <string>

#include <sstream>
#include <stdio.h>



class Helper{

public:
	//�����б�ͷ����Ϣ����
	static void setCombox(CComboBox &combox);

	//��ֱ������ϵ
	static void drawCoordinate(CClientDC &dc, int startx, int starty, int endx, int endy,int midLength);

	static void drawLine(CClientDC &dc, int **nums, int n, int len, int startx, int starty, int midLength, int endy);

	static void drawSingleLine(CClientDC &dc, int **nums, int n, int len, int startx, int starty, int midLength, int endy, int pen_num);
};


#endif // !_HELPER_H_