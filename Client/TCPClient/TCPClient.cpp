//
//// TCPClient.cpp : 定义控制台应用程序的入口点。
////
//
//#include "stdafx.h"
//#include <WinSock2.h>
//#include <stdio.h>
//#include <iostream>
//
//using namespace std;
//void sendInfo(char* str, SOCKET & socketClient);
//void close(SOCKET & socketClient);
//char* recInfo(SOCKET & socketClient);
//SOCKET BuildClinetSocket(int port, char* IP);
//bool loadWASA();
//
//DWORD WINAPI ListenSocket(LPVOID lp);
//
//
//int main()
//{
//	loadWASA();
//	SOCKET socket = BuildClinetSocket(6000, "127.0.0.1");
//	
//	CreateThread(NULL, 0, ListenSocket, (LPVOID)socket, 0, NULL);
//
//	char *str = new char[100];
//	while (true) {
//		cin >> str;
//		sendInfo(str, socket);
//	}
//
//    return 0;
//}
//
//
//DWORD WINAPI ListenSocket(LPVOID lp) {
//	SOCKET socket = (SOCKET)lp;
//	while (true) {
//		recInfo(socket);
//	}
//
//}
//
//
//void sendInfo(char* str, SOCKET & socketClient) {
//	send(socketClient, str, strlen(str) + 1, 0);
//}
//
//void close(SOCKET & socketClient) {
//	closesocket(socketClient);
//}
//
//char* recInfo(SOCKET & socketClient) {
//	char recvBuf[100];
//	recv(socketClient, recvBuf, 100, 0);
//	printf("客户端接收的信息：%s\n", recvBuf);
//	return recvBuf;
//}
//
//SOCKET BuildClinetSocket(int port, char* IP) {
//	SOCKET socketClient = socket(AF_INET, SOCK_STREAM, 0);
//	SOCKADDR_IN addrSrv;
//	addrSrv.sin_addr.S_un.S_addr = inet_addr(IP);
//	addrSrv.sin_family = AF_INET;
//	addrSrv.sin_port = htons(port);
//	connect(socketClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
//	sendInfo("0", socketClient);
//	return socketClient;
//}
//
//bool loadWASA() {
//	WORD wVersionRequested;
//	WSADATA wsaData;
//	int err;
//	//加载套接字库
//	wVersionRequested = MAKEWORD(1, 1);
//	err = WSAStartup(wVersionRequested, &wsaData);
//	if (err != 0) {
//		return false;
//	}
//	//检查对应的版本号
//	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
//		WSACleanup();
//		return false;
//	}
//	return true;
//}
//
//
//
//
//
