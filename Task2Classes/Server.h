#pragma once
#include "Comms.h"

//Student Name: Immanuel Godfrey
//Student ID: 21817368
//Course ID: CO650 - Advanced Programming


class Server :
    public Comms
{
private:
	SOCKET serverSocket, clientSocket;
	int port, RecSize, wsaerr;
	char servstr[NI_MAXSERV], hoststr[NI_MAXHOST];
	char DataValue[2000];
	sockaddr_in service;
	const WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	string userData;
public:
	Server();//constructor
	void createSocket();
	void bindSocket();
	void acceptConnection();
	void loadDLL();
	void closeSocket();
	bool recieveMsg();
	bool sendMsg();
	
};

inline Server::Server() 
{
	port = 55555;//client and server must be configured on the same port
	msgOrigin = "[Server] Enter Message : ";
}

inline void Server::loadDLL()
{
	//loads DLL by Invoking WSAStartup
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "The Winsock dll not found!" << endl;
	}
	else {
		cout << "The Winsock dll found!" << endl;
		cout << "Server DLL Status: " << wsaData.szSystemStatus << endl;
	}

}

inline void Server::createSocket()
{
	//creates socket using protocol
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
	}
	else {
		cout << "Server socket() is OK!" << endl;
	}
}

inline void Server::bindSocket()
{
	//binds server's IP address to socket
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	
	//binding expection handling code
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "bind() failed: " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
	}
	else {
		cout << "Server: bind() is OK!" << endl;
	}

	//listener exception handling code
	if (listen(serverSocket, 1) == SOCKET_ERROR)
		cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
	else
		cout << "Server: listen() is OK, waiting for connections..." << endl;
}

inline void Server::acceptConnection() 
{
	//new socket for client server communication.
	sockaddr_in ClientDesc;
	int DescSize = sizeof(ClientDesc);

	clientSocket = accept(serverSocket, (sockaddr*)&ClientDesc, &DescSize);
	//socket expection handling code
	if (clientSocket == INVALID_SOCKET) {
		cout << "accept failed: " << WSAGetLastError() << endl;
		WSACleanup();
	}

	cout << endl;
	cout << "Accepted connection" << endl;

	ZeroMemory(hoststr, NI_MAXHOST);
	ZeroMemory(servstr, NI_MAXSERV);

	// getting details from the client connecting to server (IP/Hostname and port)
	if (getnameinfo((sockaddr*)&ClientDesc, sizeof(ClientDesc), hoststr, NI_MAXHOST, servstr, NI_MAXSERV, 0) == 0)
	{
		cout << hoststr << " connected on port " << servstr << endl;
	}
	else
	{
		inet_ntop(AF_INET, &ClientDesc.sin_addr, hoststr, NI_MAXHOST);
		cout << hoststr << " connected on port " << ntohs(ClientDesc.sin_port) << endl;
	}
	//closing old socket
	closesocket(serverSocket);

	cout << "----------------------------------------------" << endl;
	cout << "type 'quit' to terminate chat app" << endl;
	cout << endl;
}


inline bool Server::sendMsg()
{
	//retriveing input from the server console
	cout << msgOrigin;
	getline(cin, userData);
	setTransferMsg(userData, msgOrigin);

	//sending server data to Client
	int ClientDesc = send(clientSocket, getTransferMsg().c_str(), getTransferMsg().size() + 1, 0);
	
	//if statement stops programme in event of a socket error
	if (ClientDesc == SOCKET_ERROR) { return 0; }

	return true;
}

inline bool Server::recieveMsg()
{
	//getting data from client
	RecSize = recv(clientSocket, DataValue, 2000, 0);

	//socket exception handling code
	if (RecSize == SOCKET_ERROR)
	{
		cerr << "Error in recv(). Quitting" << endl;
		return 0;
	}

	if (RecSize == 0)
	{
		cout << "ClientDesc disconnected " << endl;
		return 0;
	}

	//posting client output
	cout << "[Server] Recieved Output : ";
	cout << string(DataValue, 0, RecSize) << endl;
	cout << endl;

	// checking if client wants to close connection
	if ((string(DataValue, 0, RecSize)) == "quit")
	{
		//terminates app and display the respective system that initiated shutdown (Client/Server)
		cout << "[Client] ...Initiating Shutdown... " << endl;
		return 0;
	}

	return true;
}

inline void Server::closeSocket()
{
	closesocket(clientSocket);
	//frees the dll once the counter reaches zero.
	WSACleanup();

}
