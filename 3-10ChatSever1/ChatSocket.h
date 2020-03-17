#pragma once
#include <afxsock.h>
class ChatSocket :
	public CAsyncSocket
{
public:
	ChatSocket();
	virtual~ChatSocket();
	virtual void OnReceive(int nErrorCode);

};

