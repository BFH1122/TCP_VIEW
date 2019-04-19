#pragma once

#ifndef _HEADER_TCP_
#define _HEADER_TCP_

#include "stdafx.h"


#define socket_len 10

#define buf_len 128

#define start "#start"
#define end "#end"


class base;


//用于保存持久的链接socket
class MySocket {
public:
	SOCKET socket_m;
	//标识在管理队列中的下标
	int index_m;
	//保存客户端的相关消息
	SOCKADDR_IN addrClient;
public:
	void sendInfo(std::string str, long mills);
	void sendInfo(char* str, long mills);

	//此处应该传递一个接口，用于用户自定义自己的处理逻辑
	bool recvInfo(std::string & str);
};

// server 端
class TCPHelper {
	//成员变量
public:
	//用于指示socket_Arrays的下标
	int index_tcp;
	//主线程用于连接的socket
	SOCKET m_socket;

	SOCKET socket_tmp;

	MySocket *socket_Arrays;
	//保存每一个连接状态的socket

	//保存对应的线程句柄
	HANDLE *tHandles;

	std::thread *threadObj;



	//成员函数
public:
	//构造函数
	TCPHelper(int n = socket_len);

	//析构函数
	~TCPHelper();


	bool loadWASA();
	bool ListenServerSocket(int port, int time);

	//循环等待
	void waitRecRequest(base *b);


	//新接入一个socket 启动子线程，保存持久socket
	bool addMySocket(base *b, SOCKADDR_IN addrClient);

	//关闭一个持久的socket
	bool removeSocket(MySocket mySocket);


};

#endif // !_HEADER_TCP_

