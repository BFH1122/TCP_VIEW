// MyListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCMyDialog.h"
#include "MyListCtrl.h"
#include <stdio.h>


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{

}

CMyListCtrl::~CMyListCtrl()
{
}


void CMyListCtrl::insertDatas(CMyListCtrl & mList, int **nums, int n, int len) {
	
	char ch3[10] ,tmp[10];
	//����������ݡ���
	for (int j = 0; j < len; j++) {
		_itoa_s(j + 1, ch3, 10);
		mList.InsertItem(j, _T("")); // ����
		mList.SetItemText(j, 0, ch3);
		for (int i = 0; i<n; i++) {
			_itoa_s(nums[i][j], tmp, 10);
			mList.SetItemText(j, i + 1, tmp);
		}

		mList.SetItemColor(j, RGB(0, 0, 0),
			j % 2 == 0 ? RGB(255, 120, 120) : RGB(120, 120, 100));
	}
}

void CMyListCtrl::setListHeader(CMyListCtrl & mlist) {

	//����list
	DWORD dwOldStyle = mlist.GetExtendedStyle();//��ȡԭ���,����������и�ѡ����ʽ�ı��
	mlist.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT
		| LVS_EX_GRIDLINES);//�����ø�ѡ����ʽ���ڴ����LVS_CHECK��
							//��ȡ���Ŀ��

	mlist.ModifyStyle(WS_VSCROLL | WS_HSCROLL, 0);

	CRect rc;
	mlist.GetClientRect(rc);
	int nWidth = rc.Width() - 20;
	//ΪList��������Ϣ
	mlist.InsertColumn(0, _T("���"), 0, nWidth / 6);
	mlist.InsertColumn(1, _T("��һ��"), 0, nWidth / 6);
	mlist.InsertColumn(2, _T("�ڶ���"), 0, nWidth / 6);
	mlist.InsertColumn(3, _T("������"), 0, nWidth / 6);
	mlist.InsertColumn(4, _T("������"), 0, nWidth / 6);
	mlist.InsertColumn(5, _T("������"), 0, nWidth / 6);

}

BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CLineColorListCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMyListCtrl::OnNMCustomdraw)
END_MESSAGE_MAP()



// CMyListCtrl ��Ϣ�������


void CMyListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here   
	*pResult = CDRF_DODEFAULT;
	NMLVCUSTOMDRAW * lplvdr = (NMLVCUSTOMDRAW*)pNMHDR;
	NMCUSTOMDRAW &nmcd = lplvdr->nmcd;
	switch (lplvdr->nmcd.dwDrawStage)//�ж�״̬   
	{
	case CDDS_PREPAINT:
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	}
	case CDDS_ITEMPREPAINT://���Ϊ��ITEM֮ǰ��Ҫ������ɫ�ĸı�   
	{
		TEXT_BK tb;

		if (MapItemColor.Lookup(nmcd.dwItemSpec, tb))
			// ������ SetItemColor(DWORD iItem, COLORREF color) ���õ�   
			// ITEM�ź�COLORREF �������в��ң�Ȼ�������ɫ��ֵ��   
		{
			lplvdr->clrText = tb.colText;
			lplvdr->clrTextBk = tb.colTextBk;
			*pResult = CDRF_DODEFAULT;
		}
	}
	break;
	}
}
void CMyListCtrl::ClearColor()
{
	MapItemColor.RemoveAll();
}
void CMyListCtrl::SetItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor)
{
	TEXT_BK tb;
	tb.colText = TextColor;
	tb.colTextBk = TextBkColor;


	MapItemColor.SetAt(iItem, tb);//����ĳ�е���ɫ��   
	this->RedrawItems(iItem, iItem);//����Ⱦɫ   

									//this->SetCheck(iItem,1);   
	this->SetFocus();    //���ý���   
	UpdateWindow();
}
void CMyListCtrl::SetAllItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor)
{
	//INT_PTR ncount = this->GetItemCount();
	TEXT_BK tb;
	tb.colText = TextColor;
	tb.colTextBk = TextBkColor;

	if (iItem > 0)
	{
		for (DWORD numItem = 0; numItem < iItem; numItem++)
		{
			//iItem = i;   
			MapItemColor.SetAt(numItem, tb);
			this->RedrawItems(numItem, numItem);
		}
	}
	return;
}


