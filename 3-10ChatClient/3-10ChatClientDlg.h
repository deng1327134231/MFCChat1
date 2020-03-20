
// 3-10ChatClientDlg.h: 头文件
//

#pragma once
#include "ClientSocket.h"

#define MAX_MSG_SIZE 1024 //发送接收消息大小

// CMy310ChatClientDlg 对话框
class CMy310ChatClientDlg : public CDialogEx
{
// 构造
public:
	CMy310ChatClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY310CHATCLIENT_DIALOG };
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
	//afx_msg void OnCbnSelchangeCombo1();
	//afx_msg void OnBnClickedButton4();
	//afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedSendMsgButton1();
	afx_msg void OnBnClickedConnectionButton3();
public:
	ClientSocket* m_clientSocket;
	CListBox m_msg_list;
	//CTime m_time;
	CEdit m_chat_edit;
	afx_msg CString onShowMsg(CString strName, CString strMsg);
	afx_msg void OnBnClickedSevenameButton1();
	
	afx_msg void OnBnClickedClearchatButton4();
	afx_msg void OnBnClickedAotoSendCheck1();
	afx_msg void OnBnClickedDisconnectButton2();
	CComboBox m_wordColorCombo;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
