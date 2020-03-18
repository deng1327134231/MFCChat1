
// 3-10ChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "3-10ChatClient.h"
#include "3-10ChatClientDlg.h"
#include "afxdialogex.h"
#include <atlbase.h>
#include <windows.h>

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


// CMy310ChatClientDlg 对话框



CMy310ChatClientDlg::CMy310ChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY310CHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy310ChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST1, m_msg_list);
	DDX_Control(pDX, IDC_CHAT_EDIT3, m_chat_edit);
}

BEGIN_MESSAGE_MAP(CMy310ChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_SEND_MSG_BUTTON1, &CMy310ChatClientDlg::OnBnClickedSendMsgButton1)
	ON_BN_CLICKED(IDC_CONNECTION_BUTTON3, &CMy310ChatClientDlg::OnBnClickedConnectionButton3)
END_MESSAGE_MAP()


// CMy310ChatClientDlg 消息处理程序

BOOL CMy310ChatClientDlg::OnInitDialog()
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
	GetDlgItem(IDC_POINT_EDIT2)->SetWindowTextW(_T("6000"));
	GetDlgItem(IDC_IPADDR)->SetWindowTextW(_T("127.0.0.1"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy310ChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy310ChatClientDlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy310ChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





//信息发送
void CMy310ChatClientDlg::OnBnClickedSendMsgButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("####OnBnClickedSendMsgButton1");
	//	获取发送内容
	CString strMsg;
	GetDlgItem(IDC_CHAT_EDIT3)->GetWindowTextW(strMsg);
	USES_CONVERSION;
	char* msgBuff = T2A(strMsg);
	//发送数据
	m_clientSocket->Send(msgBuff, 200, 0);
	//显示发送数据
	//时间, 我,内容
	CString tmpstr;
	m_time = CTime::GetCurrentTime();
	tmpstr = m_time.Format("%X");
	tmpstr += _T("我:");
	tmpstr = tmpstr + strMsg;
	m_msg_list.AddString(tmpstr);
	m_msg_list.UpdateData(false);
	GetDlgItem(IDC_CHAT_EDIT3)->SetWindowText(_T(""));
	   
}


//实现网络连接
void CMy310ChatClientDlg::OnBnClickedConnectionButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("####OnBnClickedConnectionButton3");
	//获取端口和IP
	CString strPoint, strIp;
	GetDlgItem(IDC_POINT_EDIT2)->GetWindowTextW(strPoint);
	GetDlgItem(IDC_IPADDR)->GetWindowTextW(strIp);
	USES_CONVERSION;
	LPCSTR zePoint = (LPCSTR)T2A(strPoint);
	LPCSTR zeIp = (LPCSTR)T2A(strIp);
	TRACE("####strPoint=%s,strIp=%s", zePoint, zeIp);

	int iPoint = _ttoi(strPoint);
	//创建socket对象
	m_clientSocket = new ClientSocket;

	//创建socket
	if (!m_clientSocket->Create()) {
		TRACE("####m_clientSocket->Create  error  %d", GetLastError());
		return;
	}
	else {
		TRACE("####m_clientSocket->Create  Success");
	}


	
	//连接
	
	if (m_clientSocket->Connect(strIp, iPoint) != SOCKET_ERROR)
	{
		TRACE("####m_clientSocket->Connect error %d", GetLastError());
		return;
	}
	else {
		TRACE("####m_clientSocket->Connect Success");
		
	}
}


