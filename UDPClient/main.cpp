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

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//��������ip
	serverAddr.sin_port = htons(9999);
	int len = sizeof(serverAddr);

	char buf[] = "hello UDP server!";


	sendto(s, buf, strlen(buf), 0, (sockaddr*)&serverAddr, len);//������socket,�����͵����ݣ��������ݵĳ��ȣ���־��


	//����
	char serverBuf[512] = {};
	int recvLen = recvfrom(s, serverBuf, 512, 0, (sockaddr*)&serverAddr, &len);//����client������������
	if (recvLen > 0)
	{
		std::cout << serverBuf << std::endl;
	}


	closesocket(s);
	WSACleanup();
	system("pause");
	return 0;
	
}