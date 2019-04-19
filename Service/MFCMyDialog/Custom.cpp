#include "stdafx.h"
#include "MFCMyDialogDlg.h"
using namespace std;

//身份认证
bool Authentication(char *str);

//切分字符串，获取数组维数的相关信息
bool underOrder(char *pstr, int &n, int &len);
char* StringTochars(std::string str);


DWORD WINAPI base::deal_with(LPVOID lpParameter) {
	return NULL;
}

DWORD WINAPI custom::deal_with(LPVOID lpParameter) {
	MySocket *my_socket = (MySocket *)lpParameter;
	char *recBuf;
	//用于提示：
	char buf2[buf_len];
	char buf3[buf_len];

	string recStr = "";

	//int cc = recv(my_socket->socket_m, recBuf, buf_len, 0); //cc 是接收的字符数，暂不做处理

	//接收信息的格式不正确
	while (!my_socket->recvInfo(recStr)) {
		continue;
	}

	sprintf_s(buf3, "客户端<%s : %d> 请求身份认证", inet_ntoa(my_socket->addrClient.sin_addr),
		my_socket->addrClient.sin_port);
	cout << buf3 << endl;


	recBuf = StringTochars(recStr);


	if (!Authentication(recBuf)) {
		sprintf_s(buf2, "Authenticationfail");
		my_socket->sendInfo(buf2, 50);
		closesocket(my_socket->socket_m);

		sprintf_s(buf3, "客户端<%s : %d> 请求身份认证失败", inet_ntoa(my_socket->addrClient.sin_addr),
			my_socket->addrClient.sin_port);
		cout << buf3 << endl;
		return 0;
	}

	sprintf_s(buf2, "身份认证成功，请继续！");
	my_socket->sendInfo(buf2, 50);

	sprintf_s(buf3, "客户端<%s : %d> 请求身份认证成功", inet_ntoa(my_socket->addrClient.sin_addr),
		my_socket->addrClient.sin_port);
	cout << buf3 << endl;


	//通过身份认证之后可以一直使用此socket连接，直到客户端发送关闭命令
	while (true) {
		if (!my_socket->recvInfo(recStr)) {
			continue;
		}

		recBuf = StringTochars(recStr);

		//退出命令
		if (!strcmp("exit", recBuf)) {
			sprintf_s(buf3, "客户端<%s : %d> 请求断开连接", inet_ntoa(my_socket->addrClient.sin_addr),
				my_socket->addrClient.sin_port);
			cout << buf3 << endl;
			break;
		}
		else {
			int n = -1;
			int len = -1;
			//切分字符串,没有完成的部分

			sprintf_s(buf3, "客户端<%s : %d> 请求命令：%s", inet_ntoa(my_socket->addrClient.sin_addr),
				my_socket->addrClient.sin_port, recBuf);
			cout << buf3 << endl;

			if (!underOrder(recBuf, n, len)) {
				sprintf_s(buf2, "服务器不能解析指令 %s 请重试!", recBuf);
				my_socket->sendInfo(buf2, 50);
				continue;
			}
			//进行数组的产生
			int **nums;
			NumArrays *arr = new NumArrays();
			nums = (*arr).getArray(n, len);

			line_info *infos = new line_info();
			infos->n = n;
			infos->len = len;

			::PostMessage(hwnd, WM_DRAWLINE, 0,(LPARAM)infos);

			string str = "";
			for (int i = 0; i < n; i++) {
				//cout << "第" << i + 1 << "组:" << endl;
				str += "【";
				str += to_string(i + 1);
				str += "】：";
				for (int j = 0; j < len; j++) {
					//cout << nums[i][j] << " ";
					str += to_string(nums[i][j]) + " ";
				}
				str += "\n";
			}
			//发送数据
			my_socket->sendInfo(str, 50);
		}
	}
	char *S = "exitok";
	my_socket->sendInfo(S, 50);
	sprintf_s(buf3, "客户端<%s : %d> 连接已断开", inet_ntoa(my_socket->addrClient.sin_addr),
		my_socket->addrClient.sin_port);
	cout << buf3 << endl;

	closesocket(my_socket->socket_m);
	return 0;

}


bool underOrder(char *pstr, int &n, int &len) {
	char *d = "&";
	int i = 0;
	char *buf[3];
	//首先判断命令起始是否正确
	if (strncmp(pstr, "random", strlen("random")) != 0 || pstr[strlen("random")] != '&') {
		return false;
	}
	//正确的情况下 读出 n len 长度数值
	char *p = strtok(pstr, d);
	while (p) {
		buf[i] = p;
		i++;
		p = strtok(NULL, d);
	}
	if (i != 3) {
		return false;
	}
	//获得
	n = atoi(buf[1]);
	len = atoi(buf[2]);
	return true;
}


bool Authentication(char *pstr) {
	char *d = "&";
	int i = 0;
	char *buf[3];
	//首先判断命令起始是否正确
	if (strncmp(pstr, "login", strlen("login")) != 0 || pstr[strlen("login")] != '&') {
		return false;
	}
	//正确的情况下 读出 n len 长度数值
	char *p = strtok(pstr, d);
	while (p) {
		buf[i] = p;
		i++;
		p = strtok(NULL, d);
	}
	if (i != 3) {
		return false;
	}
	//获得
	if (!strcmp(buf[1], "admin") && !strcmp(buf[2], "admin")) {
		return true;
	}
	return false;
}

char* StringTochars(std::string str) {
	char *data = new char[strlen(str.c_str()) + 1];
	strcpy(data, str.c_str());
	return data;
}