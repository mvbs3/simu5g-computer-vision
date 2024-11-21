//
// Created by mksb@cin.ufpe.br
//

#ifndef __EXTERNALAPPCLIENTSIDE_H
#define __EXTERNALAPPCLIENTSIDE_H

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


class externalAppClientSide {
    
    public:
        externalAppClientSide();
        virtual  ~externalAppClientSide();

        void createSocket();
        void connectServer();
        int closeSocket();
         
        void sendAll(string str);
        void sendSignal(string signal);
        string receiveAll();
        string receiveSignal();
    

        const char* ADDR = "127.0.0.1";
        static const uint16_t PORT = 9595; 

        int status;
        int valread;
        int client_fd;

        struct sockaddr_in serv_addr;

};


#endif ///__EXTERNALAPPCLIENTSIDE_H