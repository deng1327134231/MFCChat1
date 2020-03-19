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

	/*
    dlg->m_time = CTime::GetCurrentTime();
    str = dlg->m_time.Format("%X");
    str += _T("���������ӳɹ�");
	*/
	CString strName = _T("");
	CString strMsg = _T("���������ӳɹ�");
	CString strShow =dlg->onShowMsg(strName, strMsg);

    dlg->m_msg_list.AddString(strShow);
    dlg->m_msg_list.UpdateData(false);


    CAsyncSocket::OnConnect(nErrorCode);

 }


//�ͻ��˽�������
void ClientSocket::OnReceive(int nErrorCode)
{
    TRACE("###ClientSocket::OnReceive");
	
	//��������
	char receveBuf[MAX_MSG_SIZE];
	CMy310ChatClientDlg* dlg = (CMy310ChatClientDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_clientSocket->Receive(&receveBuf, MAX_MSG_SIZE, 0);

	USES_CONVERSION;
	CString strMsg = A2T(receveBuf);

	//��ʾ����
	/*
	CString msgStr;
	dlg->m_time = CTime::GetCurrentTime();
	msgStr = dlg->m_time.Format("%X");
	msgStr += _T("�����:");
	msgStr = msgStr + msg;
	*/
	CString strName = _T("�����:");
	//CString strMsg = _T("���������ӳɹ�");
	CString strShow = dlg->onShowMsg(strName, strMsg);

	dlg->m_msg_list.AddString(strShow);
	dlg->m_msg_list.UpdateData(false);

	if (((CButton*)dlg->GetDlgItem(IDC_AOTO_SEND_CHECK1))->GetCheck())
	{
		CString strAutoSendMsg;
		dlg->GetDlgItem(IDC_AOTO_SEND_EDIT1)->GetWindowTextW(strAutoSendMsg);

		CString strTutoName;
		dlg->GetDlgItem(IDC_NAME_EDIT1)->GetWindowTextW(strTutoName);
		strMsg = strTutoName + _T("[�Զ��ظ�;]") + strAutoSendMsg;
		USES_CONVERSION;
		char* sendBuf = T2A(strMsg);
		dlg->m_clientSocket->Send(sendBuf, MAX_MSG_SIZE, 0);
		//CString strName = _T("");
		//CString strMsg = _T("���������ӳɹ�");
		strShow = dlg->onShowMsg(_T(""), strMsg);

		dlg->m_msg_list.AddString(strShow);
		dlg->m_msg_list.UpdateData(false);


	}

	CAsyncSocket::OnReceive(nErrorCode);
}
