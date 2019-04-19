// MyDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCMyDialog.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// MyDialog 对话框

IMPLEMENT_DYNAMIC(MyDialog, CDialog)

MyDialog::MyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_mys_STATIC, m_pic_s);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialog)
END_MESSAGE_MAP()


// MyDialog 消息处理程序
