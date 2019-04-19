
// MFCMyDialogDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "MFCMyDialog.h"
#include "MFCMyDialogDlg.h"
#include "afxdialogex.h"

#include "random.h"

#include "MyListCtrl.h"
#include <string>
#include <sstream>
#include <stdio.h>
#include "Helper.h"

using namespace std;


struct Info {
	int *nums;
	int pen;
	int len;

	int startx;
	int starty;
	int midLength;
	int endy;
};

CClientDC *CMFCMyDialogDlg::dc[5];
base *b;
TCPHelper *tcpHelper;

DWORD WINAPI drawLine(LPVOID lp);
DWORD WINAPI waitRequest(LPVOID lp);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHelps();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_HELPs, &CAboutDlg::OnHelps)
END_MESSAGE_MAP()


// CMFCMyDialogDlg 对话框



CMFCMyDialogDlg::CMFCMyDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCMYDIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CMFCMyDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mList);
	DDX_Control(pDX, IDC_COMBO3, combox);
	DDX_Control(pDX, IDC_STATIC_TEXT, static_TEXT);
}

BEGIN_MESSAGE_MAP(CMFCMyDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCMyDialogDlg::OnBnClickedOk)
	ON_COMMAND(ID_xitong, &CMFCMyDialogDlg::Onxitong)
	ON_COMMAND(ID_Setting, &CMFCMyDialogDlg::OnSetting)
	ON_COMMAND(ID_HELPs, &CMFCMyDialogDlg::OnHelps)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCMyDialogDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCMyDialogDlg::OnEnChangeEdit1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCMyDialogDlg::OnLvnItemchangedList1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CMFCMyDialogDlg::OnCbnSelchangeCombo3)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMFCMyDialogDlg::OnNMClickList1)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST1,&CMFCMyDialogDlg::OnColumnClick)
	ON_MESSAGE(WM_DRAWLINE, &CMFCMyDialogDlg::OnRecvLine)
END_MESSAGE_MAP()


// CMFCMyDialogDlg 消息处理程序

BOOL CMFCMyDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//--------------------自定义部分---------------------------------------

	//添加自定义的菜单
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	//添加表格头部
	mList.setListHeader(mList);
	
	Helper::setCombox(combox);

	for (int i = 0; i < 5; i++) {
		CMFCMyDialogDlg::dc[i] = new CClientDC(GetDlgItem(IDC_MySTATIC));
	}

	//启动服务监听线程
	CreateThread(NULL, 0, waitRequest, (LPVOID*)m_hWnd , 0, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


DWORD WINAPI waitRequest(LPVOID lp) {
	custom custom;
	b = &custom;
	b->hwnd = (HWND)lp;
	tcpHelper = new TCPHelper();
	tcpHelper->loadWASA();
	tcpHelper->ListenServerSocket(6000, 5);
	tcpHelper->waitRecRequest(b);
	return NULL;
}

void CMFCMyDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCMyDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	startx = 20;
	starty = 20;
	endx = 20;
	endy = 180;
	midLength = 650;


	//画出自己的直角坐标系
	Helper::drawCoordinate(*CMFCMyDialogDlg::dc[0],startx,starty,endx,endy,midLength);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCMyDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCMyDialogDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnOK();
}


void CMFCMyDialogDlg::Onxitong()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("点击系统按钮");

}


void CMFCMyDialogDlg::OnSetting()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("点击设置按钮");
}


void CAboutDlg::OnHelps()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("点击帮助按钮1");
}


void CMFCMyDialogDlg::OnHelps()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("点击标题组数，查看单条曲线！");
}


//点击生成按钮之后的动作
void CMFCMyDialogDlg::OnBnClickedButton1()
{
	//获取相关的参数
	char ch1[10], ch2[10];
	int nIndex = combox.GetCurSel();
	combox.GetLBText(nIndex, ch2);
	GetDlgItem(IDC_EDIT1)->GetWindowText(ch1, 10);
	n = atoi(ch2);
	len = atoi(ch1);
	if (n <= 0 || len <= 0) {
		MessageBox("请输入对应的长度与组数");
		return;
	}
	drawLines(n, len);
}


DWORD WINAPI drawLine(LPVOID lp) {
	Info* info = (Info*)lp;
	int pen = info->pen;
	int *nums = info->nums;
	int **tmp = new int*[1];
	tmp[0] = info->nums;
	Helper::drawSingleLine(*CMFCMyDialogDlg::dc[pen], tmp, 1, info->len, info->startx, info->starty, info->midLength, info->endy, info->pen);
	return 0;
}


void CMFCMyDialogDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCMyDialogDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCMyDialogDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	
}


void CMFCMyDialogDlg::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码

}

//列表内容的点击事件
void CMFCMyDialogDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int y = pNMListView->iSubItem;

	int x = pNMListView->iItem;

	if (x < len && y <= n && y>0 && x >= 0) 
		MessageBox((to_string(x + 1) + "行，" + to_string(y) + "列：" + to_string(nums[y-1][x])).c_str(),"数据提示");

	*pResult = 0;
}

void CMFCMyDialogDlg::OnColumnClick(NMHDR *pNMHDR, LRESULT *pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int m_nSortCol;
	m_nSortCol = pNMListView->iSubItem;
	
	if (m_nSortCol > n) {
		MessageBox("选中项目没有数据，请重新选择！","错误提示");
		return;
	}
	else if (m_nSortCol == 0) {
		MessageBox("您选中的是编号栏，请重新选择！", "错误提示");
		return;
	}


	MyDialog *dlg = new MyDialog;
	//dlg.DoModal();

	dlg->Create(IDD_DIALOG2, this);
	dlg->ShowWindow(SW_SHOW);
	CClientDC dcc(dlg->GetDlgItem(IDC_mys_STATIC));

	int **tmp = new int*[1];
	tmp[0] = nums[m_nSortCol-1];


	int sx = 20;
	int sy = 20;
	int mid = 520;
	int ey = 240;
	Helper::drawCoordinate(dcc, sx, sy, sx, ey, mid);
	Helper::drawLine(dcc, tmp, 1, len, sx, sy, mid, ey);

	//int **tmp = new int*[1];
	//tmp[0] = nums;

}

LRESULT CMFCMyDialogDlg::OnRecvLine(WPARAM wParam, LPARAM lParam)
{
	line_info *infos = (line_info *)lParam;
	drawLines(infos->n, infos->len);
	return LRESULT();
}

void CMFCMyDialogDlg::drawLines(int n , int len)
{
	if (nums != NULL) {
		delete nums;
		nums = NULL;
	}
	DWORD start_time = GetTickCount();
	// TODO: 在此添加控件通知处理程序代码
	mList.SetRedraw(FALSE);
	//刷新列表（清空）
	mList.DeleteAllItems();
	//lens = len;
	//根据需要产生随机数
	NumArrays *arr = new NumArrays();
	nums = (*arr).getArray(n, len);
	//进行数据的插入
	mList.insertDatas(mList, nums, n, len);
	mList.SetRedraw(TRUE);
	InvalidateRect(NULL);
	UpdateWindow();
	//多个线程画线
	for (int ii = 0; ii <n; ii++) {
		Info* info = new Info;
		info->len = len;
		info->nums = nums[ii];
		info->pen = ii;
		info->endy = endy;
		info->startx = startx;
		info->starty = starty;
		info->midLength = midLength;
		CreateThread(NULL, 0, drawLine, (LPVOID *)info, 0, NULL);
		Sleep(500);
	}
	DWORD end_time = GetTickCount();
	string str = "产生的数据：" + to_string(len) + " x " + to_string(n) + " , 耗时：" + to_string(end_time - start_time) + "ms .";
	static_TEXT.SetWindowTextA(str.c_str());
}


