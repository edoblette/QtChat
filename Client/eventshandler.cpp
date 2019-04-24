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

#include "eventshandler.hpp"

/*
 * Constructeur
 */
EventHandler::EventHandler(){
    _addrClient = nullptr;
    _addrWindow = nullptr;
    _addrConnectPage = nullptr;
    this->set_chat(nullptr, "nullptr");

}

bool EventHandler::ConnectPageSetting(ConnectPage * addrconnectPage){
    _addrConnectPage = addrconnectPage;
    while(TRUE){
        char chost[_addrConnectPage->_host.size()];
        strcpy(chost, _addrConnectPage->_host.c_str());
        //
        _addrClient->Start(_addrConnectPage->_port, chost);
        std::string connect_return(_addrClient->Connect(_addrConnectPage->_name));
        //std::cout<< "retour:" << connect_return << std::endl;
        if(connect_return.compare(0,3,"TKN") == 0){
            QMessageBox::warning(_addrConnectPage, "Erreur parametre", "Nom d'utilisateur déja pris" );
            _addrConnectPage->_name.clear();
            return 0;
        }else if(connect_return.empty()){
            QMessageBox::critical(_addrConnectPage, "Erreur Critique", "Serveur injoignable !" );
            return 0;
        }else
            break;
    }

    _addrConnectPage->close();
    _addrWindow->show();
    std::thread Talking(&Client::Talk, _addrClient);
    Talking.detach(); // a voir si c'est bon
    this->UpdateClientList("");


    return 1;
}

void EventHandler::CreateClientNWindowNPrivate(Client * addrClient, MainWindow * addrWindows, PrivateMessageTab * addrPrivateWindows){
    _addrClient = addrClient;
    _addrWindow = addrWindows;
    _addrPrivateMessages = addrPrivateWindows;


}



void EventHandler::IncomingMessage(std::string BrutMessage){
    BrutMessage.erase(remove(BrutMessage.begin(), BrutMessage.end(), '\n'), BrutMessage.end());

    std::string ConformedMessage;
    if(BrutMessage.compare(0, 3, "MSG") == 0){
        // On enlever la commande protocole
        BrutMessage.erase(0, 4);

        // On prend le nom de l'envoyeur
        std::string name(BrutMessage.substr(0, BrutMessage.find(' ')));
        name.erase(remove(name.begin(), name.end(), '\n'), name.end());

        // on nettoye le message final
        BrutMessage.erase(0, name.size() + 1);
        std::string message( BrutMessage.substr(0, BrutMessage.size()) );
        std::cout << "message[" << message << "]  name[" << name << "]" << std::endl;
        ConformedMessage = name + ": " + message;
        _addrWindow->displayMsg(ConformedMessage);

    }else if(BrutMessage.compare(0, 3, "PRV") == 0){
        // On enlever la commande protocole
        BrutMessage.erase(0, 4);

        // On prend le nom de l'envoyeur
        std::string name(BrutMessage.substr(0, BrutMessage.find(' ')));
        name.erase(remove(name.begin(), name.end(), '\n'), name.end());

        // on nettoye le message final
        BrutMessage.erase(0, name.size() + 1);
        std::string message( BrutMessage.substr(0, BrutMessage.size()) );
        std::cout << "message[" << message << "]  name[" << name << "]" << std::endl;
        ConformedMessage = name + ": " + message;

        //mettre un call back
         _addrWindow->CreateTab(name);

        if(get_chatByName(name) != nullptr){
            ConformedMessage = name + ": " + message;
            get_chatByName(name)->displayMsg(ConformedMessage); // ca bug la
        }else {
            sleep(3);
            if(get_chatByName(name) != nullptr){
                ConformedMessage = name + ": " + message;
                get_chatByName(name)->displayMsg(ConformedMessage); // ca bug la
            }
        }

        //message prive

    }else if(BrutMessage.compare(0, 3, "ARV") == 0){
        // On enlever la commande protocole
        BrutMessage.erase(0, 4);

        // On prend le nom de l'envoyeur
        std::string name(BrutMessage.substr(0, BrutMessage.find(' ')));
        name.erase(remove(name.begin(), name.end(), '\n'), name.end());

        _addrWindow->AddClientToList(name);

    }else if(BrutMessage.compare(0, 3, "LFT") == 0){
         BrutMessage.erase(0, 4);
        _addrWindow->RemClientOfList(BrutMessage);

    }else if(BrutMessage.compare(0, 3, "LST") == 0){
        // On enlever la commande protocole
        BrutMessage.erase(0, 4);
       this->UpdateClientList(BrutMessage);

    }else{
        ConformedMessage = BrutMessage;
        _addrWindow->displayMsg(ConformedMessage);
    }


}


void EventHandler::SendingMessage(std::string message){
    std::thread messagetoClient(&Client::HandleMessage, _addrClient, message );
    messagetoClient.join();
}



void EventHandler::UpdateClientList(std::string BrutMessage){
    if(BrutMessage.empty()){
        this->SendingMessage("LST");
    }else {
        std::cout << "list[" << BrutMessage << "] size:" << count(BrutMessage.begin(), BrutMessage.end(), ' ') << std::endl;
        for(long size = std::count(BrutMessage.begin(), BrutMessage.end(), ' '); size > 0 ; --size){
            std::string name(BrutMessage.substr(0, BrutMessage.find(' ')));
            BrutMessage.erase(0, name.size() + 1);
            name.erase(remove(name.begin(), name.end(), ' '), name.end());
            if(!name.empty())
                _addrWindow->AddClientToList(name);
            std::cout << "name["<<size<<"][" << name << "]" << std::endl;
        }

    }

}

void EventHandler::ErrorHandler( int platform, std::string errorFlag, std::string errorMessage){
    switch (platform) {
        // Envoyer le message d'erreur a la connectPage
        case 1:
            QMessageBox::critical(this->_addrConnectPage, QString::fromStdString(errorFlag), QString::fromStdString(errorMessage) );
            break;
        // Envoyer le message d'erreur a la MainWindows
        case 2:
            QMessageBox::critical(this->_addrWindow, QString::fromStdString(errorFlag), QString::fromStdString(errorMessage) );
            break;

        default:
            break;

    }

}

void EventHandler::Disconnecting(){
    _addrClient->Disconnect();
}
