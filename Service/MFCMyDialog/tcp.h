#pragma once

#ifndef _HEADER_TCP_
#define _HEADER_TCP_

#include "stdafx.h"


#define socket_len 10

#define buf_len 128

#define start "#start"
#define end "#end"


class base;


//���ڱ���־õ�����socket
class MySocket {
public:
	SOCKET socket_m;
	//��ʶ�ڹ�������е��±�
	int index_m;
	//����ͻ��˵������Ϣ
	SOCKADDR_IN addrClient;
public:
	void sendInfo(std::string str, long mills);
	void sendInfo(char* str, long mills);

	//�˴�Ӧ�ô���һ���ӿڣ������û��Զ����Լ��Ĵ����߼�
	bool recvInfo(std::string & str);
};

// server ��
class TCPHelper {
	//��Ա����
public:
	//����ָʾsocket_Arrays���±�
	int index_tcp;
	//���߳��������ӵ�socket
	SOCKET m_socket;

	SOCKET socket_tmp;

	MySocket *socket_Arrays;
	//����ÿһ������״̬��socket

	//�����Ӧ���߳̾��
	HANDLE *tHandles;

	std::thread *threadObj;



	//��Ա����
public:
	//���캯��
	TCPHelper(int n = socket_len);

	//��������
	~TCPHelper();


	bool loadWASA();
	bool ListenServerSocket(int port, int time);

	//ѭ���ȴ�
	void waitRecRequest(base *b);


	//�½���һ��socket �������̣߳�����־�socket
	bool addMySocket(base *b, SOCKADDR_IN addrClient);

	//�ر�һ���־õ�socket
	bool removeSocket(MySocket mySocket);


};

#endif // !_HEADER_TCP_

