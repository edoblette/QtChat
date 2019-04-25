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

class create_poll{

    public: 

        void push_back(int fd, int events){
            myPoll.emplace_back();
            myPoll.back().fd = fd;
            myPoll.back().events = events;
        }

        int size() const {
        	return myPoll.size();
        }

        pollfd* data(){
        	return myPoll.data();
        }

        pollfd& operator[](int index){
        	return myPoll[index];
        }


        pollfd* begin()
        { 
        	return &myPoll[0]; 
        }

        void erase(int index){
        	myPoll.erase(myPoll.begin()+index);
        	//return myPoll.end();  /* doit retourner fin de vector
        }
        
        // Getter
        std::vector<struct pollfd>& getPoll(){
        	return myPoll;
        }





        
    private:

        std::vector<struct pollfd> myPoll;

};