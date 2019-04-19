///* tcpdtd.cpp - main, tcpdaytimed */
//
//
//#include "stdafx.h"
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <winsock2.h>
//#include <time.h>
//#include "conio.h"
//#include <windows.h>
//#include <process.h>
//#include <math.h>
//
//#define qlen       5
//#define    wsvers    makeword(2, 0)
//#define    buflen    2000             // ��������С
//
//socket    msock, ssock;            /* master & slave sockets           */
//socket    sockets[100] = { null };
//
//int cc;
//char    *pts;                    /* pointer to time string           */
//time_t    now;                    /* current time                       */
//char buf[2000];                      /* buffer                          */
//char *input;
//handle hthread1, hthread[100] = { null };
//unsigned int threadid, threadid[100], number;
//
//struct    sockaddr_in fsin;
//struct    sockaddr_in sin;
//
//unsigned int __stdcall chat(pvoid pm)
//{
//	char buf1[2000];
//	char buf2[2000];
//	char buf3[2000];
//	char buf4[2000];
//	(void)time(&now);
//	pts = ctime(&now);
//	sockets[number] = ssock;
//	socket    sock = ssock;
//	threadid[number] = threadid;
//	unsigned int threadid = threadid;
//	sprintf(buf1, " ʱ�䣺 %s  \t���ҵ��̺߳ţ� %d ��\n", pts, threadid);
//	(void)send(sock, buf1, sizeof(buf1), 0);
//	sprintf(buf2, " �̺߳� <%d> �ͻ�<ip:%s �˿�:%d>  enter  \n", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port);
//	printf("%s ", buf2);
//	printf("\t���Զ��Ѵ����ݷ��͸����пͻ��� \n");
//	for (int i = 0; i <= number; i++)
//	{
//		if (sockets[i] != null && sockets[i] != sock)
//		{
//			(void)send(sockets[i], buf2, sizeof(buf2), 0);
//			printf(" �������̺߳�<%d>�ɹ���\n", threadid[i]);
//		}
//	}
//	printf(" \n");
//
//
//flag1:cc = recv(sock, buf3, buflen, 0);   //ccΪ���յ��ַ���
//	if (cc == socket_error || cc == 0)
//	{
//		(void)time(&now);
//		pts = ctime(&now);
//		sprintf(buf3, " �̺߳� <%d> �ͻ�<ip:%s �˿�:%d>  leave !  \n \t\tʱ�䣺 %s", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, pts);
//		sock = null;
//		sockets[number] = null;
//		closehandle(hthread[number]);
//		printf("%s ", buf3);
//		printf("\t���Զ��Ѵ����ݷ��͸����пͻ��� \n");
//		for (int i = 0; i <= number; i++)
//		{
//			if (sockets[i] != null && sockets[i] != sock)
//			{
//				(void)send(sockets[i], buf3, sizeof(buf3), 0);
//				printf(" �������̺߳�<%d>�ɹ���\n", threadid[i]);
//			}
//		}
//		printf(" \n");
//	}
//
//	else if (cc > 0)
//	{
//		(void)time(&now);
//		pts = ctime(&now);
//		sprintf(buf4, " �̺߳� <%d> �ͻ�<ip:%s �˿�:%d>˵ ��%s  \n \t\tʱ�� �� %s", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, buf3, pts);
//
//		printf("%s ", buf4);
//		printf("\t���Զ��Ѵ����ݷ��͸����пͻ��� \n");
//		for (int i = 0; i <= number; i++)
//		{
//			if (sockets[i] != null && sockets[i] != sock)
//			{
//				(void)send(sockets[i], buf4, sizeof(buf4), 0);
//				printf(" �������̺߳�<%d>�ɹ���\n", threadid[i]);
//			}
//		}
//		printf(" \n");
//
//		goto flag1;
//	}
//	(void)closesocket(sock);
//
//	return 0;
//}
//
//
///*------------------------------------------------------------------------
//* main - iterative tcp server for daytime service
//*------------------------------------------------------------------------
//*/
//void main(int argc, char *argv[])
///* argc: �����в��������� ���磺c:\> tcpdaytimed 8080
//argc=2 argv[0]="tcpdaytimed",argv[1]="8080" */
//{
//	int     alen;                    /* from-address length               */
//	wsadata wsadata;
//	char    *service = "5050";
//	wsastartup(wsvers, &wsadata);                         //���� winsock 2.2 library
//	msock = socket(pf_inet, sock_stream, 0);              //�����׽��֡�tcpЭ���=6�� udpЭ���=17
//	memset(&sin, 0, sizeof(sin));
//	sin.sin_family = af_inet;
//	sin.sin_addr.s_addr = inaddr_any;                    //ָ���󶨽ӿڵ�ip��ַ��inaddr_any��ʾ��(����)���еĽӿڡ�
//	sin.sin_port = htons((u_short)atoi(service));        //atoi--��asciiת��Ϊint��htons - ������(host)ת��Ϊ������(network), s(short) 
//	bind(msock, (struct sockaddr *)&sin, sizeof(sin));   // �󶨶˿ںţ���ip��ַ)
//	listen(msock, 5);                                    //���г���Ϊ5
//
//	printf("\t\t\t\t chat ����������� \n");
//	printf("\t\t\t\t       (server) \n");
//	(void)time(&now);
//	pts = ctime(&now);
//	printf("\t\t\t  ʱ�� ��%s", pts);
//	number = -1;
//	while (1)                                    //����Ƿ��а���
//	{
//		alen = sizeof(struct sockaddr);
//		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
//		number++;
//		hthread[number] = (handle)_beginthreadex(null, 0, chat, null, 0, &threadid);
//	}
//	(void)closesocket(msock);
//	wsacleanup();                         //ж���� winsock 2.2 library
//}