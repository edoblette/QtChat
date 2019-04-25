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
#ifndef EVENTSHANDLER_H
#define EVENTSHANDLER_H
#include "mainwindow.h"
#include "client.hpp"
#include "connectpage.h"
#include "privatemessagetab.h"
#include "chat.h"
#include <unordered_map>

class EventHandler final{


    public:
        EventHandler();

        void IncomingMessage(std::string );
        void SendingMessage(std::string );
        void Disconnecting();
        bool ConnectPageSetting(ConnectPage *);
        void UpdateClientList(std::string);
        void CreateClientNWindowNPrivate(Client * addrClient, MainWindow * addrWindows, PrivateMessageTab * addrPrivateWindows);
        void ErrorHandler( int, std::string, std::string);

    //setter
        void set_client(Client * addrClient){
            _addrClient = addrClient;
        }

        void set_windows(MainWindow * addrWindow){
            _addrWindow = addrWindow;
        }

        void set_connectPage (ConnectPage * addrconnectPage){
            _addrConnectPage = addrconnectPage;
        }
        void set_chat(chat * addrChat, std::string name){
            _adrr_vector_Chat.insert({ name, addrChat });

           std::cout << "new chat ! [" << addrChat << "][" << name <<"]" << std::endl;

        }
    //getter
        MainWindow * get_windows(){
            return  _addrWindow;
        }

        Client * get_client(){
            return  _addrClient;
        }
        ConnectPage * get_connectPage(){
            return _addrConnectPage;
        }
        PrivateMessageTab * get_privateMessage(){
            return _addrPrivateMessages;
        }

        chat * get_chatByName(std::string name){
            std::unordered_map<std::string, chat*>::const_iterator search = _adrr_vector_Chat.find(name);
             if ( search == _adrr_vector_Chat.end() )
               return nullptr;
             else
               return search->second;
        }

    private:

        MainWindow * _addrWindow;
        Client * _addrClient;
        ConnectPage * _addrConnectPage;
        PrivateMessageTab * _addrPrivateMessages;
        std::unordered_map<std::string, chat*> _adrr_vector_Chat;




};


#endif
