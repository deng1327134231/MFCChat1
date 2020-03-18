#include "pch.h"
#include "ClientSocket.h"
#include "3-10ChatClient.h"
#include "3-10ChatClientDlg.h"


ClientSocket::ClientSocket()
{

}


ClientSocket::~ClientSocket()
{

}


//
void ClientSocket::OnConnect(int nErrorCode) 
{
    TRACE("####OnConnect");
    //����֪ͨ����
    CString str;
    CMy310ChatClientDlg* dlg = (CMy310ChatClientDlg*)AfxGetApp()->GetMainWnd();
    dlg->m_time = CTime::GetCurrentTime();
    str = dlg->m_time.Format("%X");
    str += _T("���������ӳɹ�");
    dlg->m_msg_list.AddString(str);
    dlg->m_msg_list.UpdateData(false);


    CAsyncSocket::OnConnect(nErrorCode);

 }


//�ͻ��˽�������
void ClientSocket::OnReceive(int nErrorCode)
{
    TRACE("###ClientSocket::OnReceive");
	
	//��������
	char receveBuf[200];
	CMy310ChatClientDlg* dlg = (CMy310ChatClientDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_clientSocket->Receive(&receveBuf, 200, 0);

	USES_CONVERSION;
	CString msg = A2T(receveBuf);

	//��ʾ����
	CString msgStr;
	dlg->m_time = CTime::GetCurrentTime();
	msgStr = dlg->m_time.Format("%X");
	msgStr += _T("�����:");
	msgStr = msgStr + msg;
	dlg->m_msg_list.AddString(msgStr);
	//dlg->m_msg_list.UpdateData(false);

	CAsyncSocket::OnReceive(nErrorCode);
}
