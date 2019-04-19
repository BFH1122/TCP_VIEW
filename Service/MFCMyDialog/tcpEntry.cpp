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
	//需要释放的内存
}

//加载套接字函数
bool TCPHelper::loadWASA() {
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


bool TCPHelper::ListenServerSocket(int port, int time) {

	//创建套接字
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET) {
		return false;
	}
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);
	//绑定套接字
	int retvel;
	retvel = bind(m_socket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (retvel == SOCKET_ERROR) {
		return false;
	}
	//监听模式
	listen(m_socket, time);
	return true;
}

void TCPHelper::waitRecRequest(base *b)
{
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	std::cout << "服务程序启动完毕！" << std::endl;
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

	//加入到管理队列
	socket_Arrays[index_tcp] = *tmp_mySocket;

	//需要修改一下传入的处理函数
	//HANDLE hHandle = CreateThread(NULL, 0,b.deal_with, (LPVOID *)tmp_mySocket, 0, NULL);

	threadObj = new std::thread(startThread, b, (LPVOID *)tmp_mySocket);


	//等待线程执行完毕
	//threadObj->join();

	//将线程句柄加入
	//tHandles[index_tcp] = hHandle;
	//必须有
	index_tcp++;
	return true;
}

void startThread(base *b, LPVOID *lp) {
	b->deal_with(lp);
}


bool TCPHelper::removeSocket(MySocket mySocket)
{
	int index = mySocket.index_m;

	//关闭对应的线程


	//关闭对应数组的socket

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

//转化为字符串进行发送----存在冗余操作
void MySocket::sendInfo(char* str, long mills) {
	std::string ss = str;
	sendInfo(ss, mills);
}


bool MySocket::recvInfo(std::string & str)
{
	char buf1[buf_len];
	memset(buf1, 0, buf_len);
	recv(socket_m, buf1, buf_len, 0);
	//开始标识符
	str = "";
	if (!strcmp("#start", buf1)) {
		//收集传递的数据，进行整合
		//cout << "开始接收一次数据：" << endl;
		while (true) {
			memset(buf1, 0, buf_len);
			recv(socket_m, buf1, buf_len, 0);
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

char* StringTochar(std::string str) {
	char *data = new char[strlen(str.c_str()) + 1];
	strcpy(data, str.c_str());
	return data;
}
