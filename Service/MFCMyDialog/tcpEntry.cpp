#include "stdafx.h"

char* StringTochar(std::string str);
void startThread(base *b, LPVOID *lp);

TCPHelper::TCPHelper(int n)
{
	socket_Arrays = new MySocket[n];
	tHandles = new HANDLE[n];
	index_tcp = 0;
}

TCPHelper::~TCPHelper()
{
	//��Ҫ�ͷŵ��ڴ�
}

//�����׽��ֺ���
bool TCPHelper::loadWASA() {
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


bool TCPHelper::ListenServerSocket(int port, int time) {

	//�����׽���
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET) {
		return false;
	}
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);
	//���׽���
	int retvel;
	retvel = bind(m_socket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (retvel == SOCKET_ERROR) {
		return false;
	}
	//����ģʽ
	listen(m_socket, time);
	return true;
}

void TCPHelper::waitRecRequest(base *b)
{
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	std::cout << "�������������ϣ�" << std::endl;
	while (true) {
		socket_tmp = accept(m_socket, (SOCKADDR*)&addrClient, &len);
		addMySocket(b, addrClient);
	}
}

bool TCPHelper::addMySocket(base *b, SOCKADDR_IN addrClient)
{
	MySocket *tmp_mySocket = new MySocket();
	tmp_mySocket->socket_m = socket_tmp;
	tmp_mySocket->index_m = index_tcp;
	tmp_mySocket->addrClient = addrClient;

	//���뵽�������
	socket_Arrays[index_tcp] = *tmp_mySocket;

	//��Ҫ�޸�һ�´���Ĵ�����
	//HANDLE hHandle = CreateThread(NULL, 0,b.deal_with, (LPVOID *)tmp_mySocket, 0, NULL);

	threadObj = new std::thread(startThread, b, (LPVOID *)tmp_mySocket);


	//�ȴ��߳�ִ�����
	//threadObj->join();

	//���߳̾������
	//tHandles[index_tcp] = hHandle;
	//������
	index_tcp++;
	return true;
}

void startThread(base *b, LPVOID *lp) {
	b->deal_with(lp);
}


bool TCPHelper::removeSocket(MySocket mySocket)
{
	int index = mySocket.index_m;

	//�رն�Ӧ���߳�


	//�رն�Ӧ�����socket

	return true;
}



//---------------------------------------------------

void MySocket::sendInfo(std::string str, long mills)
{
	char *tmp = new char[buf_len];
	int i = 0;
	send(socket_m, start, strlen(start) + 1, 0);

	Sleep(mills);

	while (i < str.length()) {
		memset(tmp, 0, buf_len);
		tmp = StringTochar(str.substr(i, buf_len > str.length() - i
			? str.length() - i : buf_len));

		send(socket_m, tmp, strlen(tmp) + 1, 0);
		i += buf_len;

		Sleep(mills);
	}

	send(socket_m, end, strlen(end) + 1, 0);
}

//ת��Ϊ�ַ������з���----�����������
void MySocket::sendInfo(char* str, long mills) {
	std::string ss = str;
	sendInfo(ss, mills);
}


bool MySocket::recvInfo(std::string & str)
{
	char buf1[buf_len];
	memset(buf1, 0, buf_len);
	recv(socket_m, buf1, buf_len, 0);
	//��ʼ��ʶ��
	str = "";
	if (!strcmp("#start", buf1)) {
		//�ռ����ݵ����ݣ���������
		//cout << "��ʼ����һ�����ݣ�" << endl;
		while (true) {
			memset(buf1, 0, buf_len);
			recv(socket_m, buf1, buf_len, 0);
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

char* StringTochar(std::string str) {
	char *data = new char[strlen(str.c_str()) + 1];
	strcpy(data, str.c_str());
	return data;
}
