#include "stdafx.h"
#include "MFCMyDialogDlg.h"
using namespace std;

//�����֤
bool Authentication(char *str);

//�з��ַ�������ȡ����ά���������Ϣ
bool underOrder(char *pstr, int &n, int &len);
char* StringTochars(std::string str);


DWORD WINAPI base::deal_with(LPVOID lpParameter) {
	return NULL;
}

DWORD WINAPI custom::deal_with(LPVOID lpParameter) {
	MySocket *my_socket = (MySocket *)lpParameter;
	char *recBuf;
	//������ʾ��
	char buf2[buf_len];
	char buf3[buf_len];

	string recStr = "";

	//int cc = recv(my_socket->socket_m, recBuf, buf_len, 0); //cc �ǽ��յ��ַ������ݲ�������

	//������Ϣ�ĸ�ʽ����ȷ
	while (!my_socket->recvInfo(recStr)) {
		continue;
	}

	sprintf_s(buf3, "�ͻ���<%s : %d> ���������֤", inet_ntoa(my_socket->addrClient.sin_addr),
		my_socket->addrClient.sin_port);
	cout << buf3 << endl;


	recBuf = StringTochars(recStr);


	if (!Authentication(recBuf)) {
		sprintf_s(buf2, "Authenticationfail");
		my_socket->sendInfo(buf2, 50);
		closesocket(my_socket->socket_m);

		sprintf_s(buf3, "�ͻ���<%s : %d> ���������֤ʧ��", inet_ntoa(my_socket->addrClient.sin_addr),
			my_socket->addrClient.sin_port);
		cout << buf3 << endl;
		return 0;
	}

	sprintf_s(buf2, "�����֤�ɹ����������");
	my_socket->sendInfo(buf2, 50);

	sprintf_s(buf3, "�ͻ���<%s : %d> ���������֤�ɹ�", inet_ntoa(my_socket->addrClient.sin_addr),
		my_socket->addrClient.sin_port);
	cout << buf3 << endl;


	//ͨ�������֤֮�����һֱʹ�ô�socket���ӣ�ֱ���ͻ��˷��͹ر�����
	while (true) {
		if (!my_socket->recvInfo(recStr)) {
			continue;
		}

		recBuf = StringTochars(recStr);

		//�˳�����
		if (!strcmp("exit", recBuf)) {
			sprintf_s(buf3, "�ͻ���<%s : %d> ����Ͽ�����", inet_ntoa(my_socket->addrClient.sin_addr),
				my_socket->addrClient.sin_port);
			cout << buf3 << endl;
			break;
		}
		else {
			int n = -1;
			int len = -1;
			//�з��ַ���,û����ɵĲ���

			sprintf_s(buf3, "�ͻ���<%s : %d> �������%s", inet_ntoa(my_socket->addrClient.sin_addr),
				my_socket->addrClient.sin_port, recBuf);
			cout << buf3 << endl;

			if (!underOrder(recBuf, n, len)) {
				sprintf_s(buf2, "���������ܽ���ָ�� %s ������!", recBuf);
				my_socket->sendInfo(buf2, 50);
				continue;
			}
			//��������Ĳ���
			int **nums;
			NumArrays *arr = new NumArrays();
			nums = (*arr).getArray(n, len);

			line_info *infos = new line_info();
			infos->n = n;
			infos->len = len;

			::PostMessage(hwnd, WM_DRAWLINE, 0,(LPARAM)infos);

			string str = "";
			for (int i = 0; i < n; i++) {
				//cout << "��" << i + 1 << "��:" << endl;
				str += "��";
				str += to_string(i + 1);
				str += "����";
				for (int j = 0; j < len; j++) {
					//cout << nums[i][j] << " ";
					str += to_string(nums[i][j]) + " ";
				}
				str += "\n";
			}
			//��������
			my_socket->sendInfo(str, 50);
		}
	}
	char *S = "exitok";
	my_socket->sendInfo(S, 50);
	sprintf_s(buf3, "�ͻ���<%s : %d> �����ѶϿ�", inet_ntoa(my_socket->addrClient.sin_addr),
		my_socket->addrClient.sin_port);
	cout << buf3 << endl;

	closesocket(my_socket->socket_m);
	return 0;

}


bool underOrder(char *pstr, int &n, int &len) {
	char *d = "&";
	int i = 0;
	char *buf[3];
	//�����ж�������ʼ�Ƿ���ȷ
	if (strncmp(pstr, "random", strlen("random")) != 0 || pstr[strlen("random")] != '&') {
		return false;
	}
	//��ȷ������� ���� n len ������ֵ
	char *p = strtok(pstr, d);
	while (p) {
		buf[i] = p;
		i++;
		p = strtok(NULL, d);
	}
	if (i != 3) {
		return false;
	}
	//���
	n = atoi(buf[1]);
	len = atoi(buf[2]);
	return true;
}


bool Authentication(char *pstr) {
	char *d = "&";
	int i = 0;
	char *buf[3];
	//�����ж�������ʼ�Ƿ���ȷ
	if (strncmp(pstr, "login", strlen("login")) != 0 || pstr[strlen("login")] != '&') {
		return false;
	}
	//��ȷ������� ���� n len ������ֵ
	char *p = strtok(pstr, d);
	while (p) {
		buf[i] = p;
		i++;
		p = strtok(NULL, d);
	}
	if (i != 3) {
		return false;
	}
	//���
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