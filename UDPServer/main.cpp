#include <WinSock2.h>//
#include <Windows.h>//
#include <iostream>

#pragma comment(lib,"ws2_32.lib")//����Lib��̬���ӿ�

int main()
{
	WSADATA d;
	WORD w = MAKEWORD(2, 0);
	WSAStartup(w, &d);

	//����socket
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);

	//��ʼ��������ַ
	sockaddr_in  addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = INADDR_ANY;//IP��ַ
	addr.sin_port = htons(9999);//�˿ں�

	bind(s, (sockaddr*)&addr, sizeof(addr));
	char buf[512] = { 0 };
	sockaddr_in addrClient;
	int socklen = sizeof(sockaddr_in);

	std::cout << "UDP server is atart and bind to 9999" << std::endl;

	//��client��������
	char bufSend[] = "hello UDP client!";
	while (true)
	{
		sendto(s, bufSend, strlen(bufSend), 0, (sockaddr*)&addrClient, socklen);//��client��������
		int recvLen = recvfrom(s, buf, 512, 0, (sockaddr*)&addrClient, &socklen);//����client������������
		if (recvLen > 0)
		{
			std::cout << buf << std::endl;
		}
	}

	closesocket(s);
	WSACleanup();
	return 0;

}
