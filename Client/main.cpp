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

#include <iostream>
#include "eventshandler.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {
    /*
    if(argc != 3){
        cerr << "Usage: ip_address port" << endl; exit(0);
    }


    int port = atoi(argv[2]);
    Client Client(port, argv[1]);
    */
    QApplication client(argc, argv);

    EventHandler mEvent;
    ConnectPage mconnectPage;
    MainWindow mWindow;
    Client mClient;
    PrivateMessageTab mPrivateMessage;




    mEvent.CreateClientNWindowNPrivate(&mClient, &mWindow, &mPrivateMessage);

    mconnectPage.set_addrEvent(&mEvent);
    mWindow.set_addrEvent(&mEvent);
    mClient.set_addrEvent(&mEvent);
    mPrivateMessage.set_addrEvent(&mEvent);
    mconnectPage.show();


    /*
     Utiliser Getter
    newClient.displayMsg("utiliser les signals !");
    */
    return client.exec() ;

}

