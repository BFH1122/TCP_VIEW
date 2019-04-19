
// TCPClient.cpp : �������̨Ӧ�ó������ڵ㡣
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
//�ַ���תΪ char*
char* StringTochar(string str);
void printTitle();


int main()
{
	loadWASA();
	SOCKET socket ;
	printTitle();
	//�������߳����������������ķ��͵���Ϣ����Ӧ����Ļ��
	char *str = new char[buf_len];
	//���߳����������û����벢�ҷ�����Ϣ-��������

	cout << "�ͻ��˼����û������߳����� " << endl;

	while (true) {
		cin >> str;
		//��¼��ť
		if (strncmp(str, "login", strlen("login")) == 0) {
			socket = BuildClinetSocket(6000, "172.16.9.218");
			CreateThread(NULL, 0, ListenSocket, (LPVOID)socket, 0, NULL);
		}
		else if (!strcmp("exit", str)) {
			cout << "�����˳�����" << endl;
		}

		sendInfo(str, socket,50);
	}

	closesocket(socket);
    return 0;
}

void printTitle() {
	cout << "===============================================================" << endl;
	cout << "||\t\t\tʹ�ý̳�                        \t||"<< endl;
	cout << "||\t\tlogin&username&password : ��¼����\t\t||" << endl;
	cout << "||\t\texit : �˳���¼                   \t\t||" << endl;
	cout << "||\t\trandom&n&len : �������������     \t\t||" << endl;
	cout << "===============================================================" << endl;
}


DWORD WINAPI ListenSocket(LPVOID lp) {
	SOCKET socket = (SOCKET)lp;
	cout << "�ͻ��˼����������߳�����" << endl;
	while (true) {
		//������յ�����Ϣ
		string s = "";
		
		//���յ���Ϣ���ڴ���
		if (!recvInfo(socket, s)) {
			continue;
		}

		//�����ڴ�������
		char *ss = StringTochar(s);

		if (!strcmp("Authenticationfail", ss)) {
			cout << "�����֤ʧ�ܣ������½��������֤������" << endl;
			break;
		}
		//����˳��Ĺ���
		if (!strcmp("exitok", ss)) {
			cout << "�˳��ɹ�" << endl;
			break;
		}
		printf("��������Ӧ��Ϣ��\n %s\n\n", ss);
	}
	sendInfo("exit", socket,50);
	closesocket(socket);
	cout << "�ͻ����˳����ӳ���" << endl;
	return 0;
}

bool recvInfo(SOCKET socket,string & str) {
	char buf1[buf_len];
	memset(buf1, 0, buf_len);
	recv(socket, buf1, buf_len, 0);
	//��ʼ��ʶ��
	str = "";
	if (!strcmp("#start", buf1)) {
		//�ռ����ݵ����ݣ���������
		//cout << "��ʼ����һ�����ݣ�" << endl;
		while (true) {
			memset(buf1, 0, buf_len);
			recv(socket, buf1, buf_len, 0);
			//������ʶ��
			if (!strcmp("#end", buf1)) {
				break;
			}
			str += buf1;
		}
		return true;
	}
	//���յ�����Ч����Ϣ
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
	//Ӧ�ö�һ����Ӧʧ�ܵĴ���ʽ��
	return socketClient;
}

bool loadWASA() {
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	//�����׽��ֿ�
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return false;
	}
	//����Ӧ�İ汾��
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return false;
	}
	return true;
}