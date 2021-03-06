/**
    * SERVER SIDE
    * Projet Reseau
    * @teacher Pablo Rauzy <pr@up8.edu> <https://pablo.rauzy.name/teaching.html#rmpp>     
    *
    * @autor Edgar Oblette <edwardoblette@gmail.com>
    * @collegues: Lina Tlemcem 
    *             Nourdine ---
    *              
    * 20/03/2019
    */

#pragma once

#define   _SERVER_H
#define   _MAX_CLIENTS 18
#define   _MAX_TIME 300000
#define   MSG_SIZE  512
#define   TRUE 1
#define   FALSE 0
#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <string.h>
#include <cstdlib>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <poll.h>
#include <thread>
#include <algorithm>

#include "create_poll.hpp"
#include "clientStack.hpp"

class Server {
    public:
        Server(int);
        void Start();
        void Listen();
        void Manage();
        void Identity(int, char*, int);
        void Disconnect(int);
        void SendAll(std::string);
        void SendToTarget(int, std::string);
        void ErrorReporting(int, std::string);
        bool HandleMessage(char*, int);

    private:
        
        struct sockaddr_in server, client;
        int mPort;
        int mSocket;
        int mTrue;
        int mConnection;
        socklen_t mSize;    
        //vector<struct pollfd> mConnectionPool;
        create_poll mConnectionPool;
        clientStack mClientPool;


};


