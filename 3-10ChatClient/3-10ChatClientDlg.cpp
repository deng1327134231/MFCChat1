
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
	ON_BN_CLICKED(IDC_SEVENAME_BUTTON1, &CMy310ChatClientDlg::OnBnClickedSevenameButton1)
	
	ON_BN_CLICKED(IDC_CLEARCHAT_BUTTON4, &CMy310ChatClientDlg::OnBnClickedClearchatButton4)
	ON_BN_CLICKED(IDC_AOTO_SEND_CHECK1, &CMy310ChatClientDlg::OnBnClickedAotoSendCheck1)
	ON_BN_CLICKED(IDC_DISCONNECT_BUTTON2, &CMy310ChatClientDlg::OnBnClickedDisconnectButton2)
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
	//初始化控件
	GetDlgItem(IDC_CONNECTION_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_SEND_MSG_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_AOTO_SEND_CHECK1)->EnableWindow(false);
	GetDlgItem(IDC_POINT_EDIT2)->EnableWindow(true);
	GetDlgItem(IDC_IPADDR)->EnableWindow(true);

	//读取配置文件中的数据
	//读取昵称
	CString strName;
	
	CString strFileName;
	WCHAR wzeName[MAX_PATH] = { 0 };
	WCHAR Path[MAX_PATH] = { 0 };
	GetCurrentDirectoryW(MAX_PATH, Path);
	strFileName.Format(L"%ls//name.ini", Path);
	TRACE("####strFileName=%ls", strFileName);
	 DWORD dwNum= GetPrivateProfileStringW(L"client", L"name",0, wzeName,MAX_PATH, strFileName);
	 if (dwNum > 0) {
		 SetDlgItemText(IDC_NAME_EDIT1, wzeName);
		 TRACE("####wzeName=%ls", wzeName);
		 UpdateData(false);
	 }
	 else {
		 WritePrivateProfileStringW(L"client", L"name", L"客户端:", strFileName);
		 SetDlgItemText(IDC_NAME_EDIT1, L"客户端:");
		 UpdateData(false);

	 }
	

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

//显示信息格式:时间,信息(_昵称):消息
CString CMy310ChatClientDlg::onShowMsg(CString strName,CString strMsg) {
	CString strShow;
	CTime tmpTime = CTime::GetCurrentTime();
	strShow = tmpTime.Format("%X");
	strShow += strName;
	strShow += strMsg;
	return strShow;
}



//信息发送
void CMy310ChatClientDlg::OnBnClickedSendMsgButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("####OnBnClickedSendMsgButton1");
	//	获取发送内容
	CString strMsg;
	GetDlgItem(IDC_CHAT_EDIT3)->GetWindowTextW(strMsg);
	CString strName;
	GetDlgItem(IDC_NAME_EDIT1)->GetWindowTextW(strName);
	strMsg = strName + _T(":") + strMsg;
	USES_CONVERSION;
	char* msgBuff = T2A(strMsg);
	//发送数据
	m_clientSocket->Send(msgBuff, MAX_MSG_SIZE, 0);
	//显示发送数据
	//时间, 我,内容
	CString tmpstr;
#if no
	m_time = CTime::GetCurrentTime();
	tmpstr = m_time.Format("%X");
	tmpstr += _T("我:");
	tmpstr = tmpstr + strMsg;
#endif
	//CString strName = _T("");
	CString strShow = onShowMsg(_T(""), strMsg);

	m_msg_list.AddString(strShow);
	m_msg_list.UpdateData(false);

	GetDlgItem(IDC_CHAT_EDIT3)->SetWindowText(_T(""));
	   
}


//实现网络连接
void CMy310ChatClientDlg::OnBnClickedConnectionButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("####OnBnClickedConnectionButton3");
	//相关控件的控制
	GetDlgItem(IDC_CONNECTION_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_DISCONNECT_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_SEND_MSG_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_AOTO_SEND_CHECK1)->EnableWindow(true);
	GetDlgItem(IDC_POINT_EDIT2)->EnableWindow(false);
	GetDlgItem(IDC_IPADDR)->EnableWindow(false);
	
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



//保存昵称
void CMy310ChatClientDlg::OnBnClickedSevenameButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取控件昵称
	TRACE("####CMy310ChatClientDlg::OnBnClickedSevenameButton1");
	CString strName;
	GetDlgItem(IDC_NAME_EDIT1)->GetWindowTextW(strName);
	if (strName.GetLength()<=0) {
		MessageBox(L"昵称不能为空!");
		CString strName;

		CString strFileName;
		WCHAR wzeName[MAX_PATH] = { 0 };
		WCHAR Path[MAX_PATH] = { 0 };
		GetCurrentDirectoryW(MAX_PATH, Path);
		strFileName.Format(L"%ls//name.ini", Path);
		TRACE("####strFileName=%ls", strFileName);
		DWORD dwNum = GetPrivateProfileStringW(L"client", L"name", 0, wzeName, MAX_PATH, strFileName);
		if (dwNum > 0) {
			SetDlgItemText(IDC_NAME_EDIT1, wzeName);
			TRACE("####wzeName=%ls", wzeName);
			UpdateData(false);
		}
		
		return;
	}
	
	
	if (IDOK == AfxMessageBox(L"确定保存", MB_OKCANCEL))
	{
		//保存昵称
			CString strFileName;
			WCHAR Path[MAX_PATH] = { 0 };
			GetCurrentDirectoryW(MAX_PATH, Path);
			strFileName.Format(L"%ls//name.ini", Path);
			TRACE("####strFileName=%ls", strFileName);
			
			WritePrivateProfileStringW(L"client", L"name", strName, strFileName);


	}


	
}



void CMy310ChatClientDlg::OnBnClickedClearchatButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_msg_list.ResetContent();
	m_msg_list.UpdateData(false);
}


void CMy310ChatClientDlg::OnBnClickedAotoSendCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AOTO_SEND_CHECK1))->GetCheck()) {
		((CButton*)GetDlgItem(IDC_AOTO_SEND_CHECK1))->SetCheck(false);
	}
	else {
		((CButton*)GetDlgItem(IDC_AOTO_SEND_CHECK1))->SetCheck(true);
	}

}


void CMy310ChatClientDlg::OnBnClickedDisconnectButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	TRACE("####client OnBnClickedDisconnectButton2");
	//控制有关联的控件
	GetDlgItem(IDC_CONNECTION_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_SEND_MSG_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_AOTO_SEND_CHECK1)->EnableWindow(false);
	GetDlgItem(IDC_POINT_EDIT2)->EnableWindow(true);
	GetDlgItem(IDC_IPADDR)->EnableWindow(true);
	
	//断开网络
	m_clientSocket->Close();
	if (m_clientSocket != NULL) {
		delete m_clientSocket;
		m_clientSocket = NULL;
	}
	//通知网络断开信息
	CString strName = _T("");
	CString strMsg = _T("断开网络连接");
	CString strShow = onShowMsg(_T(""), strMsg);

	m_msg_list.AddString(strShow);
	m_msg_list.UpdateData(false);

}
