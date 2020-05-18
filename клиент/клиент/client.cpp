#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <locale.h>
#include <string>
#include <fstream>
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996)
using namespace std;

SOCKET podcluchenie;
//принимает свои же сообщения с сервера нужна только для того чтобы было понятно что работает
void priem(int index) {
	char msg[256];
	while (true) {
		recv(podcluchenie, msg, sizeof(msg), NULL);
		std::cout << msg << std::endl;
	}
}


int main(int argc, char* argv[]) {

	string fname = "adres.txt";
	ifstream input(fname);
	string address_s;
	string port_s;
	getline(input, address_s);

	getline(input, port_s);

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "oshibka" << std::endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int razmerada = sizeof(addr);
	//локалхост
	addr.sin_addr.s_addr = inet_addr(address_s.c_str());
	addr.sin_port = htons(stoi(port_s));
	addr.sin_family = AF_INET;

	podcluchenie = socket(AF_INET, SOCK_STREAM, NULL);
	if(connect(podcluchenie, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "oshibka podkluchenia k serveru\n";
		return 1;
	}
	std::cout << "connected\n";

	char msg[256];
	recv(podcluchenie, msg, sizeof(msg), NULL);
	std::cout << msg << std::endl;

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)priem, NULL, NULL, NULL);
	
	//отправляет сообщение на сервер в переменную msg
	char msg1[256];
	while (true) {
		std::cin.getline(msg1, sizeof(msg1));
		send(podcluchenie, msg1, sizeof(msg1), NULL);
		Sleep(10);
	}




	system("pause");
	return 0;
}
