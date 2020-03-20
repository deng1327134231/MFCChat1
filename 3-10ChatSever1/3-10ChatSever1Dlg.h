
// 3-10ChatSever1Dlg.h: 头文件
//

#pragma once
#include "ServerSocket.h"
#include "ChatSocket.h"
#define MAX_MSG_SIZE 1024 //发送接收消息大小

// CMy310ChatSever1Dlg 对话框
class CMy310ChatSever1Dlg : public CDialogEx
{
// 构造
public:
	CMy310ChatSever1Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY310CHATSEVER1_DIALOG };
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
	afx_msg void OnBnClickedCalcButton5();
	afx_msg void OnBnClickedConnectionButton2();
	ServerSocket* m_serverSocket;
	CTime m_time;
	ChatSocket* m_chatSocket;


	CListBox m_msg_list;
	
	afx_msg void OnBnClickedChatSendButton4();
	afx_msg CString onShowMsg(CString strName, CString strMsg);
	afx_msg void OnBnClickedClearButton1();
	afx_msg void OnBnClickedDisconectButton3();
	CComboBox m_wordColorCombo;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
