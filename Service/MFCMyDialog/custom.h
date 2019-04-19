#pragma once
#ifndef _HEADER_BASE_
#define _HEADER_BASE_

#include "stdafx.h"

struct line_info {
	int n;
	int len;
};

class base
{
public:
	HWND hwnd;
	virtual DWORD WINAPI deal_with(LPVOID lpParameter);
private:
};

class custom :public base {
public:
	DWORD WINAPI deal_with(LPVOID lpParameter);
private:
};

#endif // !_HEADER_BASE_
