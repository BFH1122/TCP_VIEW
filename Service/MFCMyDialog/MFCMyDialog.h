
// MFCMyDialog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCMyDialogApp: 
// �йش����ʵ�֣������ MFCMyDialog.cpp
//

class CMFCMyDialogApp : public CWinApp
{
public:
	CMFCMyDialogApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCMyDialogApp theApp;