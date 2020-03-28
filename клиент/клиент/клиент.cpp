#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <locale.h>

#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "oshibka" << std::endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int razmerada = sizeof(addr);
	//локалхост
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(11111);
	addr.sin_family = AF_INET;

	SOCKET podcluchenie = socket(AF_INET, SOCK_STREAM, NULL);
	if(connect(podcluchenie, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "oshibka podkluchenia k serveru\n";
		return 1;
	}
	std::cout << "podkluchen\n";

	system("pause");
	return 0;
}