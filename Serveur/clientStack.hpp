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


struct clientInfo{
	bool legitimacy;
	std::string name;
};

class clientStack{

    public: 
    	void createClient(){
            Identity.emplace_back();
            Identity.back().legitimacy = 0;
        }

        void eraseClient(int index){
			Identity.erase(Identity.begin()+index);
        }

        void fillClient(int index, int newLegitimacy, std::string name){
        	Identity[index].legitimacy = newLegitimacy;
        	Identity[index].name = name;
        }

   		clientInfo* begin(){ 
        	return &Identity[0]; 
        }

        clientInfo* end(){ 
        	return &Identity[Identity.size()]; 
        }


    	clientInfo& operator[](int index){
        	return Identity[index];
        }

    	int findByName(std::string name){

		    for (size_t i(0); i < Identity.size(); ++i){
		    	std::string dbName = Identity[i].name;
		    	if (!dbName.compare(name)) {
		            return i;
		        }
		    } 
        	return -1;	
        }
		
    	// Getter
    	bool getLegitimacy(int index){
    		return Identity[index].legitimacy;
    	}

    	std::string getName(int index){
    		return Identity[index].name;
    	}

        // Setter
        void setLegitimacy(int index, bool newLegitimacy){
        	Identity[index].legitimacy = newLegitimacy;
        }

        
    private:

        std::vector<struct clientInfo> Identity;

};