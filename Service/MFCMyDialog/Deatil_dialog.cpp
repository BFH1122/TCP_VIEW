// Deatil_dialog.cpp : ʵ���ļ�
//


#include "Deatil_dialog.h"
using namespace std;


// Deatil_dialog �Ի���

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


// Deatil_dialog ��Ϣ�������


void Deatil_dialog::OnStnClickedStaticdetail()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
