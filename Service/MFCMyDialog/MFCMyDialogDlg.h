
// MFCMyDialogDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "MyListCtrl.h"
#include "afxwin.h"

#include "Deatil_dialog.h"
#include "MyDialog.h"


#define WM_DRAWLINE WM_USER+1

// CMFCMyDialogDlg 对话框
class CMFCMyDialogDlg : public CDialogEx
{
// 构造
public:
	CMenu m_Menu;
	CWnd *pWnd;

	int startx;
	int starty;
	int endx;
	int endy;
	int midLength;
	CMFCMyDialogDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMYDIALOG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void Onxitong();
	afx_msg void OnSetting();
	afx_msg void OnHelps();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CMyListCtrl mList;
	afx_msg void OnCbnSelchangeCombo3();
	CComboBox combox;
	CStatic static_TEXT;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnColumnClick(NMHDR *pNMHDR, LRESULT *pResult);

	//服务器接收画线的命令
	afx_msg LRESULT OnRecvLine(WPARAM wParam, LPARAM lParam);

	void drawLines(int n, int len);

	int **nums;
	int len;
	int n;
	static base *b;
	static TCPHelper *tcpHelper;

	static CClientDC *dc[5];

};
