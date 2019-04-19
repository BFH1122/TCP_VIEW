// Deatil_dialog.cpp : 实现文件
//


#include "Deatil_dialog.h"
using namespace std;


// Deatil_dialog 对话框

IMPLEMENT_DYNAMIC(Deatil_dialog, CDialog)

Deatil_dialog::Deatil_dialog(CWnd* pParent)
	: CDialog(IDD_DIALOG1, pParent)
{

}

Deatil_dialog::~Deatil_dialog()
{
}

void Deatil_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_mySTATI, static_Detail);
}


BEGIN_MESSAGE_MAP(Deatil_dialog, CDialog)
	ON_STN_CLICKED(IDC_mySTATI, &Deatil_dialog::OnStnClickedStaticdetail)
END_MESSAGE_MAP()


// Deatil_dialog 消息处理程序


void Deatil_dialog::OnStnClickedStaticdetail()
{
	// TODO: 在此添加控件通知处理程序代码
}
