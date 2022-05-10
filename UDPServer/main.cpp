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

	//初始化监听地址
	sockaddr_in  addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = INADDR_ANY;//IP地址
	addr.sin_port = htons(9999);//端口号

	bind(s, (sockaddr*)&addr, sizeof(addr));
	char buf[512] = { 0 };
	sockaddr_in addrClient;
	int socklen = sizeof(sockaddr_in);

	std::cout << "UDP server is atart and bind to 9999" << std::endl;

	//给client发送数据
	char bufSend[] = "hello UDP client!";
	while (true)
	{
		sendto(s, bufSend, strlen(bufSend), 0, (sockaddr*)&addrClient, socklen);//给client发送数据
		int recvLen = recvfrom(s, buf, 512, 0, (sockaddr*)&addrClient, &socklen);//接收client发过来的数据
		if (recvLen > 0)
		{
			std::cout << buf << std::endl;
		}
	}

	closesocket(s);
	WSACleanup();
	return 0;

}
