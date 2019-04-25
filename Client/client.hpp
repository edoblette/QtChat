/**
    * CLIENT SIDE
    * Projet Reseau
    * @teacher Pablo Rauzy <pr@up8.edu> <https://pablo.rauzy.name/teaching.html#rmpp>
    *
    * @autor Edgar Oblette <edwardoblette@gmail.com>
    * @collegues: Lina Tlemcem
    *             Nourdine ---
    *
    * 21/04/2019
    */
#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#define   _SERVER_H
#define   _MAX_CLIENTS 10
#define   MSG_SIZE  512
#define   TRUE 1
#define   FALSE 0
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <thread>

class EventHandler;

class Client {
    friend class MainWindow;

    public:
        Client();
        void Start(int, char *);
        std::string Connect(std::string);
        void Talk();
        void ReceiveFromServer();
        void HandleMessage(std::string);
        void SendToServer(std::string );
        void Disconnect();

        //Setter

        void set_addrEvent(EventHandler * eventHandler){
               mEventHandler = eventHandler;
        }

    private:
        
        struct sockaddr_in client;
        struct hostent * mHost;
        int mPort;
        int mSocket;
        int mTrue;
        int mConnection;
       	bool mAbleToTalk;
        socklen_t mSize;
        EventHandler * mEventHandler;

};

#endif
