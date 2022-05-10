#include <WinSock2.h>//
#include <Windows.h>//
#include <iostream>

#pragma comment(lib,"ws2_32.lib")//引入Lib动态链接库

int main()
{
	WSADATA d;
	WORD w = MAKEWORD(2, 0);
	WSAStartup(w, &d);

	//创建socket
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//服务器的ip
	serverAddr.sin_port = htons(9999);
	int len = sizeof(serverAddr);

	char buf[] = "hello UDP server!";


	sendto(s, buf, strlen(buf), 0, (sockaddr*)&serverAddr, len);//参数：socket,、发送的数据，发送数据的长度，标志，


	//接收
	char serverBuf[512] = {};
	int recvLen = recvfrom(s, serverBuf, 512, 0, (sockaddr*)&serverAddr, &len);//接收client发过来的数据
	if (recvLen > 0)
	{
		std::cout << serverBuf << std::endl;
	}


	closesocket(s);
	WSACleanup();
	system("pause");
	return 0;
	
}