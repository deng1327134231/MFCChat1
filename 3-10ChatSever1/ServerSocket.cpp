#include "pch.h"
#include "ServerSocket.h"
#include "3-10ChatSever1.h"
#include "3-10ChatSever1Dlg.h"
#include "ChatSocket.h"



ServerSocket::ServerSocket()
{


}
ServerSocket::~ServerSocket()
{


}
 void ServerSocket::OnAccept(int nErrorCode)
{
	TRACE("####ServerSocket::OnAccept");
	
	CMy310ChatSever1Dlg* dlg = (CMy310ChatSever1Dlg*)AfxGetApp()->GetMainWnd();
	dlg->m_chatSocket = new ChatSocket;
	
	Accept(*dlg->m_chatSocket);

	CString str;
	dlg->m_time = CTime::GetCurrentTime();

	str = dlg->m_time.Format("%X");
	str += _T("客户端连接成功");
	dlg->m_msg_list.AddString(str);
	
	dlg->m_msg_list.UpdateData(false);
	
	CAsyncSocket::OnAccept(nErrorCode);
}
