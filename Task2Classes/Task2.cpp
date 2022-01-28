// Task2Classes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Client.h"
#include "Comms.h"
#include "Server.h"
#include <iostream>

//Student Name: Immanuel Godfrey
//Student ID: 21817368
//Course ID: CO650 - Advanced Programming

void displayStudent()
{
    cout << endl;
    cout << "//Student Name: Immanuel Godfrey" << endl;
    cout << "//Student ID: 21817368" << endl;
    cout << "//Course ID: CO650 - Advanced Programming" << endl;
    cout << endl;
}

int main()
{
   
   /* CLIENT and SERVER can be defined or undefined to create conditional 
    compilation that can compile four different programs.
    by default CLIENT and SERVER are defined to showcase the full app
    functionality
    */
#define CLIENT //enables CLIENT code compilation
#define SERVER //enables 

#if !defined(CLIENT) && !defined(SERVER)
    //if both CLIENT and SERVER are undefined no objects are compiled.
    std::cout << "----NO CLIENT OR SERVER HAS BEEN DEFINED----\n";
#elif defined(SERVER) && !defined(SERVER)
    //only compiles the server application variant 
    std::cout << "------------ONLY SERVER DEFINED------------\n";
    displayStudent();//display student details

    //Creating Dynamic Server object
    Server* myServer;
    myServer = new Server();

    //loads object DLL
    myServer->loadDLL();

    //creates object Socket
    myServer->createSocket();

    //server object awaiting connection
    myServer->bindSocket();
    myServer->acceptConnection();

    //closes socket
    myServer->closeSocket();


#elif defined(CLIENT) && !defined(SERVER)
    //only compiles the client application variant 
    std::cout << "------------ONLY CLIENT DEFINED------------\n";
   
    displayStudent();//display student details

    //Creating Dynamic Client object
    Client* myClient;
    myClient = new Client();
    
    //loads object DLL
    myClient->loadDLL();

    //creates object Socket
    myClient->createSocket();

    //client tries to connect
    myClient->connectServer();

    //closes the client and server sockets
    myClient->closeSocket();


#else //runs complete chat app

    std::cout << "------------CHAT APP------------\n";
    displayStudent();//display student details

    //Creating Dynamic Server object
    Server* myServer;
    myServer = new Server();

    //Creating Dynamic Client object
    Client* myClient;
    myClient = new Client();

    //loads object DLL
    myServer->loadDLL();
    myClient->loadDLL();

    //creates object Socket
    myServer->createSocket();
    myClient->createSocket();

    //connects client and server objects
    myServer->bindSocket();
    myClient->connectServer();
    myServer->acceptConnection();

    //loops chat app until 'quit' message triggers bool flag
    while (true)
    {
        //sends data from client to server object
        if (myClient->sendMsg() == false) { break; }

        //server object recieves data from client object
        if (myServer->recieveMsg() == false) { break; }

        //sends data from server to client object
        if (myServer->sendMsg() == false) { break; }

        //client objects recieves data from server object
        if (myClient->recieveMsg() == false) { break; }
    }

    //closes the client and server sockets
    myClient->closeSocket();
    myServer->closeSocket();
#endif

    
   

    




    
    
   
   

}
