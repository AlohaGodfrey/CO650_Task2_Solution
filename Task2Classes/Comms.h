#pragma once
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <string>
#include "iostream"
#pragma comment(lib, "ws2_32.lib")

//Student Name: Immanuel Godfrey
//Student ID: 21817368
//Course ID: CO650 - Advanced Programming

using namespace std;
class Comms
{
private:
	//Message used in Client and Server Class
	string transferMsg;
protected:
	string msgOrigin;
public:
	Comms();//constructor
	~Comms();//destructor

	//virtual functions
	virtual void loadDLL() = 0;
	virtual void createSocket() = 0;
	virtual bool sendMsg() = 0;
	virtual bool recieveMsg() = 0;
	virtual void closeSocket() = 0;

	//getter and setter for string
	void setTransferMsg(string msg, string msgOrigin);
	string getTransferMsg() const;
	
};

inline Comms::Comms() {

}

inline Comms::~Comms()
{
}

//Setter memeber function for Message string
inline void Comms::setTransferMsg(string msg, string msgOrigin)
{
	string userData;
	//exception handling for empty messages
	try {
		if (!msg.empty()){transferMsg = msg;}
		else { throw(msg); }
	}
	catch (string msg) { 
		cout << "Text entry must not be empty!" << endl; 
		cout << msgOrigin;
		getline(cin, userData);
		setTransferMsg(userData, msgOrigin);
	}
}

//Accessor for Message string
inline string Comms::getTransferMsg() const
{
	return transferMsg;
}




