#pragma once
#include <afxsock.h>
class ServerSocket :
	public CAsyncSocket
{
public:
	ServerSocket();
	virtual~ServerSocket();
	virtual void OnAccept(int nErrorCode); 

};

