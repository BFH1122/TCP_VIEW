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
//#define    buflen    2000             // 缓冲区大小
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
//	sprintf(buf1, " 时间： %s  \t【我的线程号： %d 】\n", pts, threadid);
//	(void)send(sock, buf1, sizeof(buf1), 0);
//	sprintf(buf2, " 线程号 <%d> 客户<ip:%s 端口:%d>  enter  \n", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port);
//	printf("%s ", buf2);
//	printf("\t将自动把此数据发送给所有客户！ \n");
//	for (int i = 0; i <= number; i++)
//	{
//		if (sockets[i] != null && sockets[i] != sock)
//		{
//			(void)send(sockets[i], buf2, sizeof(buf2), 0);
//			printf(" 发送至线程号<%d>成功！\n", threadid[i]);
//		}
//	}
//	printf(" \n");
//
//
//flag1:cc = recv(sock, buf3, buflen, 0);   //cc为接收的字符数
//	if (cc == socket_error || cc == 0)
//	{
//		(void)time(&now);
//		pts = ctime(&now);
//		sprintf(buf3, " 线程号 <%d> 客户<ip:%s 端口:%d>  leave !  \n \t\t时间： %s", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, pts);
//		sock = null;
//		sockets[number] = null;
//		closehandle(hthread[number]);
//		printf("%s ", buf3);
//		printf("\t将自动把此数据发送给所有客户！ \n");
//		for (int i = 0; i <= number; i++)
//		{
//			if (sockets[i] != null && sockets[i] != sock)
//			{
//				(void)send(sockets[i], buf3, sizeof(buf3), 0);
//				printf(" 发送至线程号<%d>成功！\n", threadid[i]);
//			}
//		}
//		printf(" \n");
//	}
//
//	else if (cc > 0)
//	{
//		(void)time(&now);
//		pts = ctime(&now);
//		sprintf(buf4, " 线程号 <%d> 客户<ip:%s 端口:%d>说 ：%s  \n \t\t时间 ： %s", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, buf3, pts);
//
//		printf("%s ", buf4);
//		printf("\t将自动把此数据发送给所有客户！ \n");
//		for (int i = 0; i <= number; i++)
//		{
//			if (sockets[i] != null && sockets[i] != sock)
//			{
//				(void)send(sockets[i], buf4, sizeof(buf4), 0);
//				printf(" 发送至线程号<%d>成功！\n", threadid[i]);
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
///* argc: 命令行参数个数， 例如：c:\> tcpdaytimed 8080
//argc=2 argv[0]="tcpdaytimed",argv[1]="8080" */
//{
//	int     alen;                    /* from-address length               */
//	wsadata wsadata;
//	char    *service = "5050";
//	wsastartup(wsvers, &wsadata);                         //加载 winsock 2.2 library
//	msock = socket(pf_inet, sock_stream, 0);              //生成套接字。tcp协议号=6， udp协议号=17
//	memset(&sin, 0, sizeof(sin));
//	sin.sin_family = af_inet;
//	sin.sin_addr.s_addr = inaddr_any;                    //指定绑定接口的ip地址。inaddr_any表示绑定(监听)所有的接口。
//	sin.sin_port = htons((u_short)atoi(service));        //atoi--把ascii转化为int，htons - 主机序(host)转化为网络序(network), s(short) 
//	bind(msock, (struct sockaddr *)&sin, sizeof(sin));   // 绑定端口号（和ip地址)
//	listen(msock, 5);                                    //队列长度为5
//
//	printf("\t\t\t\t chat 多人聊天程序 \n");
//	printf("\t\t\t\t       (server) \n");
//	(void)time(&now);
//	pts = ctime(&now);
//	printf("\t\t\t  时间 ：%s", pts);
//	number = -1;
//	while (1)                                    //检测是否有按键
//	{
//		alen = sizeof(struct sockaddr);
//		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
//		number++;
//		hthread[number] = (handle)_beginthreadex(null, 0, chat, null, 0, &threadid);
//	}
//	(void)closesocket(msock);
//	wsacleanup();                         //卸载载 winsock 2.2 library
//}