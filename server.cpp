#include "server.h"

bool Server::InitSocket()
{
	WSADATA wsaData = { 0 };  
	int iResult = 0;  
	// Initialize Winsock  
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);  
	if (iResult != 0) {  
		wprintf(L"WSAStartup failed: %d\n", iResult);  
		return false;  
	}  

	struct sockaddr_in servaddr;  
	int bResult = 0;  
	recsocket = INVALID_SOCKET;  
	recsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);  
	if (recsocket == INVALID_SOCKET) {  
		wprintf(L"socket failed with error: %ld\n", GetLastError());  
		WSACleanup();  
		return false;  
	}  

	servaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  
	servaddr.sin_family = AF_INET;  
	servaddr.sin_port = htons(port);  

	bResult = bind(recsocket, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in));  
	if (bResult == INVALID_SOCKET) {  
		wprintf(L"bind failed with error: %ld\n", GetLastError());  
		closesocket(recsocket);  
		WSACleanup();  
		return false;  
	}

	if (listen(recsocket, SOMAXCONN) == SOCKET_ERROR)  
	{  
		wprintf(L"listen failed with error: %ld\n", GetLastError());  
		closesocket(recsocket);  
		WSACleanup();  
		return false;  
	}  
}


DWORD Server::Threadrec(LPVOID para)
{
	DWORD dwThreadId = *(DWORD *)para;
	SOCKET acceptsock = INVALID_SOCKET;  

	printf("Accepting ...\n");  
	while(true)
	{	// listen socket
		if ((acceptsock = accept(recsocket, NULL, NULL)) == INVALID_SOCKET)  
		{  
			wprintf(L"accept failed with error: %ld\n", GetLastError());  
			closesocket(acceptsock);  
			WSACleanup();  
		}  
		else  
		{	// get data
			char* buf;
			struct st_DataPack* pack = &datapack;
			printf("Client connected.\n"); 
			size_t size = recv(recsocket, buf, sizeof(buf), MSG_WAITALL);  
  
			if (size != SOCKET_ERROR)  
			{  
				memcpy(pack,buf,sizeof(buf));
				if ( pack->seq = lastseq + 1)
				{
					fwrite(pack->Data, sizeof(pack->Data), 1, fp);  
					lastseq = pack->seq;
				}
			}
			else
			{
				fclose(fp);
				delete fp;
				printf("read finish.\n");  
				return 1;
			}
			delete buf;
			delete pack;
		}
	}
}
DWORD Server::Threadsend(LPVOID para)
{
	return 1;
}

bool Server::openfile(string filename)
{
	FILE *fp = NULL;  
	if ((fp = fopen("image.jpg", "wb+")) == NULL)  
	{  
		closesocket(recsocket);  
		wprintf(L"fopen function failed with error: %ld\n", WSAGetLastError());  
		WSACleanup();  
		return false;  
	}  
}
