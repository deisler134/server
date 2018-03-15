#include <stdio.h>
#include <string>
#include <iostream>
#include <winsock2.h>
#include <windows.h>  

//#define UM_MSG1 (WM_USER + 1)  
//#define UM_MSG2 (WM_USER + 2)  

#define DATABUF_SIZE	512
using namespace std;

struct st_DataPack {
	int seq;
	char Data[DATABUF_SIZE] ;
};

class Server{
public:
	Server(int port):port(port),lastseq(0){};
	//string addr_ip;
	int port;
	bool InitSocket();				//init socket
	DWORD Threadrec(LPVOID para);	//receive data
	DWORD Threadsend(LPVOID para);
	bool openfile(string filename);	//save date

private:
	SOCKET recsocket;				
	SOCKET sendsocket;
	FILE *fp;
	st_DataPack datapack;			//data packet
	int lastseq;					//data sequence
		
};