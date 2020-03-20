
// 3-10ChatSever1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "3-10ChatSever1.h"
#include "3-10ChatSever1Dlg.h"
#include "afxdialogex.h"
#include <atlbase.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy310ChatSever1Dlg 对话框



CMy310ChatSever1Dlg::CMy310ChatSever1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY310CHATSEVER1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy310ChatSever1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST1, m_msg_list);
	DDX_Control(pDX, IDC_COLOR_COMBO1, m_wordColorCombo);
}

BEGIN_MESSAGE_MAP(CMy310ChatSever1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CALC_BUTTON5, &CMy310ChatSever1Dlg::OnBnClickedCalcButton5)
	ON_BN_CLICKED(IDC_CONNECTION_BUTTON2, &CMy310ChatSever1Dlg::OnBnClickedConnectionButton2)
	
	ON_BN_CLICKED(IDC_CHAT_SEND_BUTTON4, &CMy310ChatSever1Dlg::OnBnClickedChatSendButton4)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON1, &CMy310ChatSever1Dlg::OnBnClickedClearButton1)
	ON_BN_CLICKED(IDC_DISCONECT_BUTTON3, &CMy310ChatSever1Dlg::OnBnClickedDisconectButton3)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMy310ChatSever1Dlg 消息处理程序

BOOL CMy310ChatSever1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	//控制有关联的控件
	GetDlgItem(IDC_CONNECTION_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_DISCONECT_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_CHAT_SEND_BUTTON4)->EnableWindow(false);
	GetDlgItem(IDC_POINT_EDIT3)->EnableWindow(true);

	//comboBox控件初始化
	m_wordColorCombo.AddString(_T("黑色"));
	m_wordColorCombo.AddString(_T("紅色"));
	m_wordColorCombo.AddString(_T("綠色"));
	m_wordColorCombo.AddString(_T("藍色"));

	m_wordColorCombo.SetCurSel(0);

	SetDlgItemTextW(IDC_COLOR_COMBO1, _T("黑色"));

	//设置默认端口
	GetDlgItem(IDC_POINT_EDIT3)->SetWindowText(_T("6000"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy310ChatSever1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy310ChatSever1Dlg::OnPaint()
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
		CPaintDC dc(this);

		CRect rect;
		GetClientRect(rect);

		CDC tmpCdc;
		tmpCdc.CreateCompatibleDC(&tmpCdc);

		CBitmap bmpBrackmap;
		bmpBrackmap.LoadBitmapW(IDB_BITMAP6);

		BITMAP bmp;
		bmpBrackmap.GetBitmap(&bmp);
		CBitmap* oldBitmap = tmpCdc.SelectObject(&bmpBrackmap);

		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &tmpCdc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);


		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy310ChatSever1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy310ChatSever1Dlg::OnBnClickedCalcButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}

//显示信息格式:时间,信息(_昵称):消息
CString CMy310ChatSever1Dlg::onShowMsg(CString strName, CString strMsg) {
	CString strShow;
	CTime tmpTime = CTime::GetCurrentTime();
	strShow = tmpTime.Format("%X");
	strShow += strName;
	strShow += strMsg;
	return strShow;
}

void CMy310ChatSever1Dlg::OnBnClickedConnectionButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	TRACE("####ClickedConnectionButton2");
	//控制相关控件
	GetDlgItem(IDC_CONNECTION_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_DISCONECT_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHAT_SEND_BUTTON4)->EnableWindow(true);
	GetDlgItem(IDC_POINT_EDIT3)->EnableWindow(false);

	//获取端口
	CString strPoint;
	GetDlgItem(IDC_POINT_EDIT3)->GetWindowTextW(strPoint);
	
	USES_CONVERSION;
	LPCSTR zePoint = (LPCSTR)T2A(strPoint);
	
	TRACE("strPoint=%s", zePoint);
	int iPoint = _ttoi(strPoint);
	//创建对象
	m_serverSocket = new ServerSocket;

	
	//创建socket
	if (!m_serverSocket->Create(iPoint))
	{
		TRACE("####m_serverSocket->Create errorCode  %d", GetLastError());
		return;
	}
	else {
		TRACE("####m_serverSocket->Create Success");
		
	}
	//监听socket
	
	if (!m_serverSocket->Listen())
	{
		TRACE("####m_serverSocket->Listen errorCode  %d", GetLastError());
		return;
	}
	else {
		TRACE("####m_serverSocket->Listen Success");
		
	}
	
	
	/*
	CString str;	
	m_time = CTime::GetCurrentTime();
	str = m_time.Format("%X");
	str += _T("服务启动成功");
	*/

	CString strName = _T("");
	CString strMsg = _T("服务启动成功");
	CString strShow = onShowMsg(strName, strMsg);
	m_msg_list.AddString(strShow);

	m_msg_list.UpdateData(false);
	
}



//服务端信息发送
void CMy310ChatSever1Dlg::OnBnClickedChatSendButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//打日志
	TRACE("####server ::OnBnClickedChatSendButton4");
	//	获取发送内容
	CString strMsg;
	GetDlgItem(IDC_CHAT_EDIT2)->GetWindowTextW(strMsg);
	USES_CONVERSION;
	char* msgBuff = T2A(strMsg);
	//发送数据
	m_chatSocket->Send(msgBuff, MAX_MSG_SIZE, 0);
	//显示发送数据
	//时间, 我,内容
	/*
	CString tmpstr;
	m_time = CTime::GetCurrentTime();
	tmpstr = m_time.Format("%X");
	tmpstr += _T("服务端:");
	tmpstr = tmpstr + strMsg;
	*/
	CString strName = _T("服务端:");
	//CString strMsg = _T("服务启动成功");
	CString strShow = onShowMsg(strName, strMsg);

	m_msg_list.AddString(strShow);
	m_msg_list.UpdateData(false);
	GetDlgItem(IDC_CHAT_EDIT2)->SetWindowText(_T(""));
}

//清除历史记录
void CMy310ChatSever1Dlg::OnBnClickedClearButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_msg_list.ResetContent();
}

//网络断开
void CMy310ChatSever1Dlg::OnBnClickedDisconectButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//控制相关控件
	TRACE("####Serverce OnBnClickedDisconectButton3");
	//控制有关联的控件
	GetDlgItem(IDC_CONNECTION_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_DISCONECT_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_CHAT_SEND_BUTTON4)->EnableWindow(false);
	GetDlgItem(IDC_POINT_EDIT3)->EnableWindow(true);

	//关闭服务
	m_serverSocket->Close();
	if (m_serverSocket != NULL) {
		delete m_serverSocket;
		m_serverSocket = NULL;
	}

	if (m_chatSocket != NULL) {
		delete m_chatSocket;
		m_chatSocket = NULL;
	}
	//关闭服务通知
	CString strName = _T("");
	CString strMsg = _T("服务器关闭");
	CString strShow = onShowMsg(_T(""), strMsg);

	m_msg_list.AddString(strShow);
	m_msg_list.UpdateData(false);
}


HBRUSH CMy310ChatSever1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	TRACE("####server OnCtlColor");
	CString strColor;
	m_wordColorCombo.GetWindowTextW(strColor);
	if (IDC_MSG_LIST1 == pWnd->GetDlgCtrlID() || IDC_CHAT_EDIT2 == pWnd->GetDlgCtrlID())
	{
		if (strColor == L"黑色") 
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == L"紅色")
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (strColor == L"綠色") 
		{
			pDC->SetTextColor(RGB(0, 255, 0));
		}
		else if (strColor == L"藍色") 
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}

	}
	return hbr;
}
