//
// Created by mksb@cin.ufpe.br
//

#include "externalAppClientSide.h"

externalAppClientSide::externalAppClientSide(){}
externalAppClientSide::~externalAppClientSide(){}

void externalAppClientSide::createSocket(){
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        printf("\n Socket creation error \n");
    }
}

void externalAppClientSide::connectServer(){
    serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, ADDR, &serv_addr.sin_addr)
		<= 0) 
    {
        printf(
            "\nInvalid address/ Address not supported \n");
	}
    if ((status
    = connect(client_fd, (struct sockaddr*)&serv_addr,
            sizeof(serv_addr)))
    < 0) 
    {
        printf("\nConnection Failed \n");
	}
}

int externalAppClientSide::closeSocket(){
    close(client_fd);
	return 0;
}

void externalAppClientSide::sendAll(string str){
    const char* msg = str.c_str();
    send(client_fd, msg, strlen(msg), 0);
    printf("Message sent ...\n");
}

void externalAppClientSide::sendSignal(string signal){

}

string externalAppClientSide::receiveAll(){
    char buffer[1024] = { 0 };
    valread = read(client_fd, buffer, 1024);
	// printf("%s\n", buffer);
    string str(buffer);
    return str;
}

string externalAppClientSide::receiveSignal(){
    return "hey";
}