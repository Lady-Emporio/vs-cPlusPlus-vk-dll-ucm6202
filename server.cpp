#include <winsock2.h>
#include <Ws2tcpip.h>
#include <Winsock2.h> 
#include <ws2tcpip.h> 
#include <synchapi.h> 
#include "windows.h"


#include "server.h"
#include <thread>
#include "clearSky.h"


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")


void foreverListener(IAddInDefBase* eventMen, std::string ip, int port, std::string user, std::string password) {
	myLog("this is daemon.");

	//Begin create then try take
	/*
	HANDLE dllMutex = CreateMutex(NULL, FALSE, "ucm6202_mutexDll");
	if (NULL == dllMutex) {
		myLog("Mutex create error.", eventMen);
		return;
	}
	DWORD result = WaitForSingleObject(dllMutex, 0);
	if (result != WAIT_OBJECT_0) {
		myLog("Mutex already lock.", eventMen);
		return;
	}
	*/
	myLog("Mutex take OK. Begin work.");
	std::string str_login = "Action: login\r\nUsername: " + user + "\r\nSecret: " + password + "\r\n\r\n";
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		myLog("WSAStartup falled");
		return;
	}

	SOCKET _s;
	_s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_s == INVALID_SOCKET)
	{
		myLog("Error create socket.");
		return;
	}
	else {
		myLog("Good create socket.");
	}
	
	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(port);
	ServerAddr.sin_addr.s_addr = inet_addr(ip.c_str());
	int RetCode = connect(_s, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if (RetCode != 0)
	{
		myLog("Error connect: " + std::to_string(WSAGetLastError()));
		closesocket(_s);
		return;
	}

	if (!sendall(_s, str_login)) {
		myLog("ERROR send:"+ str_login);
		return;
	}
	std::string message="";
	while (1) {

		struct timeval tv;
		tv.tv_sec = 60;
		tv.tv_usec = 0;

		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(_s, &readfds);
		myLog("select begin");
		int result = select(
			NULL,
			&readfds,
			NULL,
			NULL,
			&tv
		);
		if (SOCKET_ERROR == result) {
			myLog("Select error");
			return;
		}
		if (0 == result) {
			myLog("timeout" + std::to_string(result));
			return;
		}
		myLog("select check"+std::to_string(result));

		char buf[400 * 8 * 2];
		int byte_count;
		byte_count = recv(_s, buf, sizeof(buf)-1, 0);
		if (0 == byte_count) {
			myLog("Get message about close.");
			return;
		}
		else if (SOCKET_ERROR == byte_count) {
			myLog("recv error:" + std::to_string(WSAGetLastError()));
			return;
		}
		//myLog(std::to_string(byte_count)+" "+ std::to_string(sizeof(buf)));
		buf[byte_count] = '\0';

		message += buf;
		size_t endLastMessage=message.rfind("\r\n\r\n");
		if (endLastMessage != std::string::npos) {
			std::string fullMessages(message, 0, endLastMessage);
			std::string halfMessage(message, endLastMessage + 1);
			message = halfMessage;
			myLog(fullMessages);
			std::wstring messageW(fullMessages.begin(), fullMessages.end());
			WCHAR_T* wsData = messageW.data();
			if (!eventMen->ExternalEvent(L"ucm6202_vk", L"newEvent", wsData)) {
				myLog("can not send in 1C");
			}
		}
		


	}
}

void threadMain(IAddInDefBase* eventMen, std::string ip, int port, std::string user, std::string password) {
	while (true) {
		foreverListener(eventMen, ip, port, user, password);
		Sleep(2000);
	}
}

void runListen(IAddInDefBase* eventMen, std::string ip, int port, std::string user, std::string password)
{
	//std::thread thread(foreverListener, eventMen, ip,port,user,password);
	std::thread thread(threadMain, eventMen, ip,port,user,password);
	thread.detach();
	//thread.join();
	myLog("thread.detach run.");
}


bool isCanRead(int s)
{
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(s, &readfds);
	int result = select(
		NULL,
		&readfds,
		NULL,
		NULL,
		&tv
	);
	if (0 == result) {
		return false;
	}
	return true;
}


bool sendall(int fd, std::string message)
{
	const char* buf = message.data();
	int len = message.size();
	int total = 0;         
	int bytesleft = len;
	int n = -1;

	while (total < len) {
		n = send(fd, buf + total, bytesleft, 0);
		if (n == -1) {
			//+ handling error. /////////////////////////////
			if (0 != total) {
				myLog("Can not send message. !!!!!! ALREADY SEND something!!!!!!. SEND:'" + std::to_string(total) + "' bytes.");
			}
			else {
				myLog("Can not send message. Nothing not send. Zero send.");
			}
			break;
			//- handling error. /////////////////////////////
		}
		total += n;
		bytesleft -= n;
	}

	return (total == len);
}
