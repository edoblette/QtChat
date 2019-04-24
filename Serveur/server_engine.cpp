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

#include "server.h"

/** Sets the needed info
 *  @param port to listen on
 */
Server::Server(int setport) {
    mPort = setport;
}
 /** Starts the server
  */
void Server::Start() {
    mSocket = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "Socket succesfully started." << std::endl;
    if (setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, &mTrue, sizeof(int)) < 0) {
        std::cout << "[setsockopt] :: ERROR" << std::endl;
        exit(EXIT_FAILURE);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(mPort);
    server.sin_addr.s_addr = INADDR_ANY;
    mSize = sizeof(server);
    if(bind(mSocket, (struct sockaddr*)(&server), mSize) < 0) {
        std::cout << "[bind] :: ERROR" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(fcntl(mSocket, F_SETFL, O_NONBLOCK) < 0){
        std::cout << "[fcntl] :: ERROR" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Starting server on port " << mPort << std::endl;
    std::cout << "LIVE" << std::endl;
}


 /** Listens to the incoming packets
  */
void Server::Listen() {
    if(listen(mSocket, 10) < 0){
          std::cout << "[listen ] :: ERROR" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Listening." << std::endl;


    mConnectionPool.push_back(mSocket, POLLIN);
    mClientPool.createClient();

    // On donne un joli nom a notre serveur
    mClientPool.fillClient(0, TRUE, "serveur");

    
    
    int poll_statut;
    

    while(1) {
        
       
        // On lance un poll pour savoir si il y'a du nouveau coté socket
        if ((poll_statut = poll(  mConnectionPool.data(), mConnectionPool.size() , _MAX_TIME)) < 0) {
          perror("poll");
          continue;
        }
        else if (poll_statut== 0) { /* timeout */
          if (mConnectionPool.size() == 1) { /* pas de client pendant 5min, on quitte */
            std::cout << "noboby -> disconnection" << std::endl;
            close(mConnectionPool[0].fd);
            break;
          }
        }

        // Attente des nouveau clients
        if ( mConnectionPool[0].revents & POLLIN) { /* nouveau client */
            mConnection = accept(mSocket, (struct sockaddr*)(&client), &mSize);
            if( mConnection < 0)
                std::cout << "[accept]  :: ERROR " << std::endl;
            else{
                mClientPool.createClient();
                mConnectionPool.push_back(mConnection, POLLIN);

                if (mConnectionPool.size() == _MAX_CLIENTS) { /* déjà plein */
                    
                    SendToTarget(mConnectionPool.size() - 1, "Sorry, server full!" );
                    Disconnect(mConnectionPool.size() - 1);
                }

                // WHO - On verifie son identiee
                Identity(mConnectionPool.size() - 1, nullptr, 1);
                //std::cout << "Handling connection : " << mConnection << std::endl;
            }
            
        }

        // Affiche tout les clients
        /*
         for (int i = 0; i < mConnectionPool.size(); i++)
            std::cout << "user[" << i << "]" << " :: " << mConnectionPool[i].fd <<std::endl;
        */

        // Si poll se declenche, on regarde qui parle 
        std::thread ManageOnEvent(&Server::Manage, this);
        ManageOnEvent.detach(); // a voir si c'est bon
        sleep(1);

    }
}

void Server::Manage(){
        int status = 0;
        char buffer[MSG_SIZE + 1];
        memset(buffer,0,sizeof(buffer));

            std::cout << "---------------------------------------------" << std::endl;
        for (int i = 1; i < mConnectionPool.size(); i++) {
            if ((mConnectionPool[i].revents & POLLIN) == 0) continue;
            std::cout << "Client connected ["<< mConnectionPool.size() - 1 << "/" << _MAX_CLIENTS << "]" << std::endl;
                
                status = read(mConnectionPool[i].fd, buffer, sizeof(buffer));
                if(status < 0){
                    std::cout << "[read] :: ERROR" << std::endl ; 
                }
                else if(status == 0) {

                   Disconnect(i);
       
                } else {
                    // Verifie Id
                    if(mClientPool.getLegitimacy(i) == FALSE){
                        std::cout << "Client id[" << i << "] not identified" << std::endl;
                        Identity(i, buffer, 2);
                           
                        
                    }
                    else{
                        // Gere les messages
                        if(HandleMessage(buffer, i) == FALSE)
                            SendToTarget(i, "ERR");
                        std::cout << "Message receved from client id[" << i << "]" << std::endl;
                    }
                } 
            
        }
}



 /** Authentifie le nouveau client
  * @param prend le mConnection
  */
void Server::Identity(int socketIdentity, char* buffer, int state){
    switch(state){
        // Identification ?
        case 1:
        {      
            std::cout << "ID :: "<< socketIdentity <<std::endl;
            SendToTarget(socketIdentity, "WHO");
            break;
        }

        // Verification
        case 2:{
            std::string verifBuffer(buffer);
            if((verifBuffer.compare(0, 3, "IAM")) == 0){
                // On ajoute son nom et on le certifie
                std::string name = verifBuffer.substr(4, verifBuffer.find(' ') + 4);

                //on nettoye le nom de toute impuretées
                name.erase(remove(name.begin(), name.end(), ' '), name.end());
                name.erase(remove(name.begin(), name.end(), '\n'), name.end());
                if(name.size() <= 1){
                    std::cout << "Error name too short : [" << name << "]" << std::endl;
                    ErrorReporting(socketIdentity, "ERR");
                    break;

                }else{
                    // Verifier si le nom n'existe pas deja
                    if(mClientPool.findByName(name) > 0){
                        ErrorReporting(socketIdentity, "TKN");
                        break;
                    }

                    // On ajoute le nom du client et on le rend legitime de parler
                    mClientPool.fillClient(socketIdentity, TRUE, name);
                    std::cout << "Client identified [" << name << "] with id[" <<  socketIdentity << "]" << std::endl;
                    // On annonce le nouveau client
                    SendAll("ARV " + name);

                } 
            }else
                Identity(socketIdentity, nullptr, 1);

            break;
        }
       
    }
   
}

 /** Analyse message recu
  *  @param prend le buffer de reception
  */
bool Server::HandleMessage(char* buffer, int clientIdentity) {
    std::string message = buffer;

    if (message.compare(0,3,"MSG") == 0){
        // Message client to everybody
        message = "MSG "+ mClientPool.getName(clientIdentity) + message.substr(3);
        message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
        SendAll(message + "\n");
        return TRUE;

    }else if(message.compare(0,3,"PRV") == 0){
        // Message prive client to client
        int iTarget;
        std::string sTarget = message.substr(4);

        // On separe le destinataire du message
        message = sTarget.substr(sTarget.find(' ') + 1);
        sTarget = sTarget.substr(0, sTarget.find(' '));

        // On determine le destinataire
        iTarget = mClientPool.findByName(sTarget); 
        if( iTarget <= 0)
            return FALSE;
        std::cout << "Sending private message from id[" << clientIdentity << "] to [" << sTarget << "] with id[" << iTarget << "]" << std::endl;
        message = "PRV "+ mClientPool.getName(clientIdentity) + " "+ message;
        SendToTarget(iTarget, message);
        return TRUE;

    }else if(message.compare(0,3,"BYE") == 0){
        // Sortie Client
        std::cout << "Client with id[" << clientIdentity << "] send disconnection request" <<std::endl;
        Disconnect(clientIdentity);
        return TRUE;

    }else if(message.compare(0,3,"LST") == 0){
        // Sortie Client
        std::string list("LST ");
        for (int i = 1; i < mConnectionPool.size(); i++) {
            list.append(mClientPool.getName(i));
            list.append(" ");
        }
        SendToTarget(clientIdentity, list);
        return TRUE;

    }else
        return FALSE;
    

}


 /** Envoye un msg à tous les utilisateurs
  * @param prend le buffer a envoyer
  */
void Server::SendAll(std::string message){
    for (int i = 1; i < mConnectionPool.size(); i++) {
        SendToTarget(i,  message);
    }   
}

/** Envoye un msg à un seul destinataire
  * @param prend l'identifant du destinataire et le messsage a envoyer
  */
void Server::SendToTarget(int clientIdentity, std::string message){
    message += '\n';
    char buffer[message.size()];
    strcpy(buffer, message.c_str());
    send(mConnectionPool[clientIdentity].fd, buffer, strlen(buffer), 0);  
}

 /** Envoye l'erreur à l'utilisateur
  * @param prend le code Erreur à envoyer
  */
void Server::ErrorReporting(int socketIdentity, std::string errorFlag){
    SendToTarget(socketIdentity,  errorFlag);
}


 /** Deconnecte le client
  * @param prend le mConnection
  */
void Server::Disconnect(int clientIdentity){
    close(mConnectionPool[clientIdentity].fd); 
    SendAll("LFT " + mClientPool.getName(clientIdentity)); 
    mClientPool.eraseClient(clientIdentity);
    mConnectionPool.erase(clientIdentity); // index
    std::cout << "Client with id[" << clientIdentity << "] have been disconnected and erased, reason: disconnection." << std::endl;
}

