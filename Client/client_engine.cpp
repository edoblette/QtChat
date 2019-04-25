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


/** Sets the needed info
 *  @param port to listen on
 */
Client::Client() {
    mPort = 0;
    mHost = nullptr;
    mAbleToTalk = FALSE;
}   
 /** Start the client
  */
void Client::Start(int port, char *serverIp) {
    mPort = port;
    mHost = gethostbyname(serverIp);
    std::cout << "mPort:" << mPort << "    mHost: " << mHost << std::endl;
    if(mHost == NULL){
        perror("gethostbyname");
        mEventHandler->ErrorHandler( 1, "Erreur Critique", "Serveur injoignable");
        exit(EXIT_FAILURE);
    }
    bzero(&client, sizeof(client)); 
    // assign IP, PORT 
    client.sin_family = AF_INET; 
    client.sin_addr.s_addr = *((uint32_t *) mHost->h_addr);
    client.sin_port = htons(mPort);

    mSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(mSocket < 0){
        std::cerr<<"[socket] :: ERROR" << std::endl; 
        mEventHandler->ErrorHandler( 1, "Erreur Critique", "Port injoignable");
        exit(EXIT_FAILURE);
    }
    mSize = sizeof(client);
}
 /** Connect the server 
  */
std::string Client::Connect(std::string name){
    //try to connect...

    if(connect(mSocket, (sockaddr*) &client, mSize) < 0){
        std::cerr<<"Unable to connect the server  " <<std::endl; 
        mEventHandler->ErrorHandler( 1, "Erreur Critique", "Serveur injoignable !");
        exit(EXIT_FAILURE);
    }else{
        std::cout << "Connected to the server!" << std::endl;
        std::cout << "LIVE" << std::endl;
        char buffer[4];
        read(mSocket, buffer, sizeof(buffer));
        SendToServer("IAM " + name);
        memset(&buffer, 0, sizeof(buffer)*2); //clear the buffer
        read(mSocket, buffer, sizeof(buffer));

        std::string connect_return(buffer);
        return connect_return;
    }

  
}
 /** Talm with the server 
  */
void Client::Talk(){
    std::cout << "LETS CHAT" << std::endl;

    mAbleToTalk = TRUE;
    // On crée un thread pour receptionner tout les messages
    std::thread messageStream(&Client::ReceiveFromServer, this);

    messageStream.join();
    if(mAbleToTalk)
        Disconnect();

}

/** Recois les données du serveur
  */
void Client::ReceiveFromServer(){
    char buffer[1500];
    while(mAbleToTalk){
        std::cout << mAbleToTalk << std::endl;
        memset(&buffer, 0, sizeof(buffer)); //clear the buffer

        if(read(mSocket, buffer, sizeof(buffer)) == 0){
            std::cout << "Server offline !!!" << std::endl;
            mEventHandler->IncomingMessage("Serveur injoignable ! - Deconnection dans 5 sec");
            sleep(5);
            mEventHandler->Disconnecting();
            //mEventHandler->ErrorHandler(2, "Erreur Critique", "Serveur injoignable !");
            mAbleToTalk = FALSE;
            //break;
        }else{
            mEventHandler->IncomingMessage(buffer);
            std::cout << "Server: " << buffer << std::endl;
        }

    }
}

/** Analyse ce que tape le client
  */
void Client::HandleMessage(std::string message){
        std::cout <<"message recu = " << message <<std::endl;
        if(!message.empty()){
            SendToServer(message);
            // a changer
        }
}


/** Envoi un msg au server
  * @param prend le message 
  */
void Client::SendToServer(std::string message){
    std::cout <<"message envoyer " << message <<std::endl;
    message += '\n';
    char buffer[message.size()];
    strcpy(buffer, message.c_str());
    send(mSocket, buffer, strlen(buffer), 0);  
}

/** Deconnecte le client
  * @param prend le mConnection
  */
void Client::Disconnect(){
        mAbleToTalk = FALSE;
        SendToServer("BYE");
        close(mSocket);
        std::cout << "Disconnect successful ! - Adios muchachos" << std::endl;
}
