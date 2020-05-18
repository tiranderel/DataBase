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

SOCKET Podcluch[100];
int schetchic = 0;
//принимает сообщения клиента в msg 
void priem(int index) {
	
	char msg[256];
	while (true) {
		recv(Podcluch[index], msg, sizeof(msg), NULL);
		for (int i = 0; i < schetchic; i++) {
			//отсюда можно писать все что угодно я написал проверку (см в заметки клиента)
			send(Podcluch[index], msg, sizeof(msg), NULL);
		}
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

	SOCKET proslushka = socket(AF_INET, SOCK_STREAM, NULL);
	bind(proslushka, (SOCKADDR*)&addr, sizeof(addr));
	listen(proslushka, SOMAXCONN);

	SOCKET newpodcluch;

	for(int i = 0; i<100; i++){
		newpodcluch = accept(proslushka, (SOCKADDR*)&addr, &razmerada);

		if(newpodcluch == 0) {
			std::cout << "oshibka s podclucheniem\n";
		}
		else {
			std::cout << "Vse horosho, client podcluchilsia\n";
			//здесь в самом начале он отправляет сообщение может понадобится
			char msg[256] = "pechatai";
			send(newpodcluch, msg, sizeof(msg), NULL);

			Podcluch[i] = newpodcluch;
			schetchic++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)priem, (LPVOID)(i), NULL, NULL);

		}
	}
	

	system("pause");

	return 0;
}
