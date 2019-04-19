#pragma once


typedef struct
{
	COLORREF colText;
	COLORREF colTextBk;
}TEXT_BK;


// CMyListCtrl

class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

public:
	CMyListCtrl::CMyListCtrl();
	void CMyListCtrl::setListHeader(CMyListCtrl & mlist);
	void CMyListCtrl::insertDatas(CMyListCtrl & mList, int **nums, int n, int len);
	virtual CMyListCtrl::~CMyListCtrl();

public:
	void SetItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor);   //ÉèÖÃÄ³Ò»ÐÐµÄÇ°¾°É«ºÍ±³¾°É«
	void SetAllItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor);//ÉèÖÃÈ«²¿ÐÐµÄÇ°¾°É«ºÍ±³¾°É«  
	void ClearColor();                                                          //Çå³ýÑÕÉ«Ó³Éä±í 
	CMap<DWORD, DWORD&, TEXT_BK, TEXT_BK&> MapItemColor;
protected:
	void CMyListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	DECLARE_MESSAGE_MAP()
};


