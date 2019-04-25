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

#include <iostream>
#include "server.h"

using namespace std;
int main(int argc, char *argv[]) {
    if(argc != 2){
        cerr << "Usage: port" << endl; exit(EXIT_FAILURE);
    }
    
    Server Server(atoi(argv[1]));
    Server.Start();
    Server.Listen();
    return 0;
}