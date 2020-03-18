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
void ChatSocket::OnReceive(int nErrorCode)
{
	TRACE("####ChatSocket::OnReceive");
	//��������
	char receveBuf[200];
	CMy310ChatSever1Dlg* dlg = (CMy310ChatSever1Dlg*)AfxGetApp()->GetMainWnd();
	dlg->m_chatSocket->Receive(&receveBuf, 200, 0);
	USES_CONVERSION;

	CString msg = A2T(receveBuf);

	//��ʾ����
	CString msgStr;
	dlg->m_time = CTime::GetCurrentTime();
	msgStr = dlg->m_time.Format("%X");
	msgStr += _T("�ͻ���:");
	msgStr = msgStr + msg;
	dlg->m_msg_list.AddString(msgStr);
	dlg->m_msg_list.UpdateData(false);

	CAsyncSocket::OnReceive(nErrorCode);
}

