// MyListCtrl.cpp : 实现文件
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
	//插入随机数据　　
	for (int j = 0; j < len; j++) {
		_itoa_s(j + 1, ch3, 10);
		mList.InsertItem(j, _T("")); // 插入
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

	//控制list
	DWORD dwOldStyle = mlist.GetExtendedStyle();//获取原风格,可以在添加有复选框样式的表格
	mlist.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT
		| LVS_EX_GRIDLINES);//若设置复选框样式，在此添加LVS_CHECK宏
							//获取表格的宽度

	mlist.ModifyStyle(WS_VSCROLL | WS_HSCROLL, 0);

	CRect rc;
	mlist.GetClientRect(rc);
	int nWidth = rc.Width() - 20;
	//为List插入列信息
	mlist.InsertColumn(0, _T("编号"), 0, nWidth / 6);
	mlist.InsertColumn(1, _T("第一组"), 0, nWidth / 6);
	mlist.InsertColumn(2, _T("第二组"), 0, nWidth / 6);
	mlist.InsertColumn(3, _T("第三组"), 0, nWidth / 6);
	mlist.InsertColumn(4, _T("第四组"), 0, nWidth / 6);
	mlist.InsertColumn(5, _T("第五组"), 0, nWidth / 6);

}

BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CLineColorListCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMyListCtrl::OnNMCustomdraw)
END_MESSAGE_MAP()



// CMyListCtrl 消息处理程序


void CMyListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here   
	*pResult = CDRF_DODEFAULT;
	NMLVCUSTOMDRAW * lplvdr = (NMLVCUSTOMDRAW*)pNMHDR;
	NMCUSTOMDRAW &nmcd = lplvdr->nmcd;
	switch (lplvdr->nmcd.dwDrawStage)//判断状态   
	{
	case CDDS_PREPAINT:
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	}
	case CDDS_ITEMPREPAINT://如果为画ITEM之前就要进行颜色的改变   
	{
		TEXT_BK tb;

		if (MapItemColor.Lookup(nmcd.dwItemSpec, tb))
			// 根据在 SetItemColor(DWORD iItem, COLORREF color) 设置的   
			// ITEM号和COLORREF 在摸板中查找，然后进行颜色赋值。   
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


	MapItemColor.SetAt(iItem, tb);//设置某行的颜色。   
	this->RedrawItems(iItem, iItem);//重新染色   

									//this->SetCheck(iItem,1);   
	this->SetFocus();    //设置焦点   
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


