
// TCPClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include <stdio.h>
#include <cstring>
#include <stdio.h>
#include <iostream>

#define buf_len 129
#define start "#start"
#define end "#end"

using namespace std; 
void sendInfo(char* str, SOCKET & socketClient, long mills);
void sendInfo(char* str, SOCKET & socketClient, long mills);
bool recvInfo(SOCKET socket, string & str);
SOCKET BuildClinetSocket(int port, char* IP);
bool loadWASA();


DWORD WINAPI ListenSocket(LPVOID lp);
//字符串转为 char*
char* StringTochar(string str);
void printTitle();


int main()
{
	loadWASA();
	SOCKET socket ;
	printTitle();
	//创建子线程用来监听服务器的发送的消息，反应在屏幕上
	char *str = new char[buf_len];
	//主线程用来监听用户输入并且发送消息-》服务器

	cout << "客户端监听用户输入线程启动 " << endl;

	while (true) {
		cin >> str;
		//登录按钮
		if (strncmp(str, "login", strlen("login")) == 0) {
			socket = BuildClinetSocket(6000, "172.16.9.218");
			CreateThread(NULL, 0, ListenSocket, (LPVOID)socket, 0, NULL);
		}
		else if (!strcmp("exit", str)) {
			cout << "输入退出命令" << endl;
		}

		sendInfo(str, socket,50);
	}

	closesocket(socket);
    return 0;
}

void printTitle() {
	cout << "===============================================================" << endl;
	cout << "||\t\t\t使用教程                        \t||"<< endl;
	cout << "||\t\tlogin&username&password : 登录功能\t\t||" << endl;
	cout << "||\t\texit : 退出登录                   \t\t||" << endl;
	cout << "||\t\trandom&n&len : 请求随机数功能     \t\t||" << endl;
	cout << "===============================================================" << endl;
}


DWORD WINAPI ListenSocket(LPVOID lp) {
	SOCKET socket = (SOCKET)lp;
	cout << "客户端监听服务器线程启动" << endl;
	while (true) {
		//保存接收到的消息
		string s = "";
		
		//接收的消息存在错误
		if (!recvInfo(socket, s)) {
			continue;
		}

		//不存在错误的情况
		char *ss = StringTochar(s);

		if (!strcmp("Authenticationfail", ss)) {
			cout << "身份认证失败，请重新进行身份认证操作！" << endl;
			break;
		}
		//完成退出的功能
		if (!strcmp("exitok", ss)) {
			cout << "退出成功" << endl;
			break;
		}
		printf("服务器响应信息：\n %s\n\n", ss);
	}
	sendInfo("exit", socket,50);
	closesocket(socket);
	cout << "客户端退出连接程序" << endl;
	return 0;
}

bool recvInfo(SOCKET socket,string & str) {
	char buf1[buf_len];
	memset(buf1, 0, buf_len);
	recv(socket, buf1, buf_len, 0);
	//开始标识符
	str = "";
	if (!strcmp("#start", buf1)) {
		//收集传递的数据，进行整合
		//cout << "开始接收一次数据：" << endl;
		while (true) {
			memset(buf1, 0, buf_len);
			recv(socket, buf1, buf_len, 0);
			//结束标识符
			if (!strcmp("#end", buf1)) {
				break;
			}
			str += buf1;
		}
		return true;
	}
	//接收的是无效的信息
	str = "";
	return false;
}

char* StringTochar(string str) {
	char *data;
	int lens = str.length();
	data = (char *)malloc((lens + 1) * sizeof(char));
	memset(data, 0, lens + 1);
	str.copy(data, lens, 0);
	return data;
}



void sendInfo(string str, SOCKET & socketClient,long mills) {

	char *tmp = new char[buf_len];
	int i = 0;
	send(socketClient, start, strlen(start) + 1, 0);

	Sleep(mills);

	while (i < str.length()) {
		memset(tmp, 0, buf_len);
		tmp = StringTochar(str.substr(i, buf_len > str.length() - i
			? str.length() - i : buf_len));

		send(socketClient, tmp, strlen(tmp) + 1, 0);
		i += buf_len;

		Sleep(mills);
	}

	send(socketClient, end, strlen(end) + 1, 0);

}
void sendInfo(char* str, SOCKET & socketClient, long mills) {
	std::string ss = str;
	sendInfo(ss, socketClient, mills);
}

SOCKET BuildClinetSocket(int port, char* IP) {
	SOCKET socketClient = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(IP);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);
	connect(socketClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	//应该多一个响应失败的处理方式，
	return socketClient;
}

bool loadWASA() {
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	//加载套接字库
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return false;
	}
	//检查对应的版本号
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return false;
	}
	return true;
}