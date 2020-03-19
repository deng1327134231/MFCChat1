#include "pch.h"
#include "ChatSocket.h"
#include "3-10ChatSever1.h"
#include "3-10ChatSever1Dlg.h"



ChatSocket::ChatSocket()
{

}
ChatSocket::~ChatSocket()
{

}
//���ܿͻ�����Ϣ����ʾ
void ChatSocket::OnReceive(int nErrorCode)
{
	TRACE("####ChatSocket::OnReceive");
	//��������
	char receveBuf[MAX_MSG_SIZE];
	CMy310ChatSever1Dlg* dlg = (CMy310ChatSever1Dlg*)AfxGetApp()->GetMainWnd();
	dlg->m_chatSocket->Receive(&receveBuf, MAX_MSG_SIZE, 0);
	USES_CONVERSION;

	CString strMsg = A2T(receveBuf);

	//��ʾ����
	/*
	CString msgStr;
	dlg->m_time = CTime::GetCurrentTime();
	msgStr = dlg->m_time.Format("%X");
	msgStr += _T("�ͻ���:");
	msgStr = msgStr + msg;
	*/
	CString strName = _T("");
	
	CString strShow = dlg->onShowMsg(strName, strMsg);

	dlg->m_msg_list.AddString(strShow);
	dlg->m_msg_list.UpdateData(false);

	CAsyncSocket::OnReceive(nErrorCode);
}

