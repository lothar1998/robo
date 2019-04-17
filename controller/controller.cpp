//
// Created by Piotr Kuglin on 2019-04-15.
//

#include "controller.h"
#include "action_interface/action.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <string>


using namespace std;


controller::controller(action **tasks, size_t sizeTasks, unsigned int port, string ip_addr, int domain, int type, int protocol) {

    this->tasks = tasks;
    this->sizeTasks=sizeTasks;

    try {
        socketHandle=socket(domain,type,protocol);
    }catch (errno_t e) {
        cout<<"socket creation exception: "<<e<<endl;
    }

    address.sin_family = domain;
    inet_pton(domain,ip_addr.c_str(),&address.sin_addr);
    address.sin_port=htons(port);

    try{
        bind(socketHandle,(struct sockaddr_int *)&address,sizeof(address));
    }catch (errno_t e){
        cout<<"bind exception: "<<e<<endl;
    }


    try {
        listen(socketHandle,1);
    }catch (errno_t e){
        cout<<"listen exception: "<<e<<endl;
    }

    try{
        clientSocketHandle=accept(socketHandle,(struct sockaddr*)&clientAddress,(socklen_t*)&clientAddressSize);
    }catch (errno_t e){
        cout<<"accept exception: "<<e<<endl;
    }
}

controller::~controller() {
    try {
        shutdown(socketHandle,SHUT_RDWR);
    }catch (errno_t e){
        cout<<"shutdown exception: "<<e<<endl;
    }

}

int * controller::readMessage() {
    try{
        recv(clientSocketHandle,&buffer,32,MSG_WAITALL);
    }catch (errno_t e){
        cout<<"recv exception: "<<e<<endl;
    }

    return &buffer;
}



void controller::takeAction() {
    for(int i=0;i<sizeTasks;i++)
        tasks[i]->takeAction(buffer);
}

void controller::run() {
    int i=2;

    do{
        readMessage();
        //TODO check propriety of message

        takeAction();
    }while(i--); //TODO stop condition
}