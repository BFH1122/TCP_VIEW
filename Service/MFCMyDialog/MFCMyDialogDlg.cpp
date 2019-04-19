
// MFCMyDialogDlg.cpp : ʵ���ļ�
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

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCMyDialogDlg �Ի���



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


// CMFCMyDialogDlg ��Ϣ�������

BOOL CMFCMyDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//--------------------�Զ��岿��---------------------------------------

	//����Զ���Ĳ˵�
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	//��ӱ��ͷ��
	mList.setListHeader(mList);
	
	Helper::setCombox(combox);

	for (int i = 0; i < 5; i++) {
		CMFCMyDialogDlg::dc[i] = new CClientDC(GetDlgItem(IDC_MySTATIC));
	}

	//������������߳�
	CreateThread(NULL, 0, waitRequest, (LPVOID*)m_hWnd , 0, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCMyDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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


	//�����Լ���ֱ������ϵ
	Helper::drawCoordinate(*CMFCMyDialogDlg::dc[0],startx,starty,endx,endy,midLength);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCMyDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCMyDialogDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CDialogEx::OnOK();
}


void CMFCMyDialogDlg::Onxitong()
{
	// TODO: �ڴ���������������
	MessageBox("���ϵͳ��ť");

}


void CMFCMyDialogDlg::OnSetting()
{
	// TODO: �ڴ���������������
	MessageBox("������ð�ť");
}


void CAboutDlg::OnHelps()
{
	// TODO: �ڴ���������������
	MessageBox("���������ť1");
}


void CMFCMyDialogDlg::OnHelps()
{
	// TODO: �ڴ���������������
	MessageBox("��������������鿴�������ߣ�");
}


//������ɰ�ť֮��Ķ���
void CMFCMyDialogDlg::OnBnClickedButton1()
{
	//��ȡ��صĲ���
	char ch1[10], ch2[10];
	int nIndex = combox.GetCurSel();
	combox.GetLBText(nIndex, ch2);
	GetDlgItem(IDC_EDIT1)->GetWindowText(ch1, 10);
	n = atoi(ch2);
	len = atoi(ch1);
	if (n <= 0 || len <= 0) {
		MessageBox("�������Ӧ�ĳ���������");
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCMyDialogDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMFCMyDialogDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	
}


void CMFCMyDialogDlg::OnCbnSelchangeCombo3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}

//�б����ݵĵ���¼�
void CMFCMyDialogDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int y = pNMListView->iSubItem;

	int x = pNMListView->iItem;

	if (x < len && y <= n && y>0 && x >= 0) 
		MessageBox((to_string(x + 1) + "�У�" + to_string(y) + "�У�" + to_string(nums[y-1][x])).c_str(),"������ʾ");

	*pResult = 0;
}

void CMFCMyDialogDlg::OnColumnClick(NMHDR *pNMHDR, LRESULT *pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int m_nSortCol;
	m_nSortCol = pNMListView->iSubItem;
	
	if (m_nSortCol > n) {
		MessageBox("ѡ����Ŀû�����ݣ�������ѡ��","������ʾ");
		return;
	}
	else if (m_nSortCol == 0) {
		MessageBox("��ѡ�е��Ǳ������������ѡ��", "������ʾ");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mList.SetRedraw(FALSE);
	//ˢ���б���գ�
	mList.DeleteAllItems();
	//lens = len;
	//������Ҫ���������
	NumArrays *arr = new NumArrays();
	nums = (*arr).getArray(n, len);
	//�������ݵĲ���
	mList.insertDatas(mList, nums, n, len);
	mList.SetRedraw(TRUE);
	InvalidateRect(NULL);
	UpdateWindow();
	//����̻߳���
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
	string str = "���������ݣ�" + to_string(len) + " x " + to_string(n) + " , ��ʱ��" + to_string(end_time - start_time) + "ms .";
	static_TEXT.SetWindowTextA(str.c_str());
}


