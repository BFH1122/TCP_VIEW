#pragma once
#include "stdafx.h"
#include "MFCMyDialog.h"

#include "MFCMyDialogDlg.h"

#include "afxdialogex.h"

#include "Helper.h"

#include <iostream>
#include <string>
#include "afxwin.h"

// Deatil_dialog �Ի���

class Deatil_dialog : public CDialog
{
	DECLARE_DYNAMIC(Deatil_dialog)

public:
	Deatil_dialog(CWnd* pParent=NULL);   // ��׼���캯��
	virtual ~Deatil_dialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic static_Detail;
	afx_msg void OnStnClickedStaticdetail();
	afx_msg void OnStnClickedStaticdetails();
};
