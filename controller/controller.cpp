//
// Created by Piotr Kuglin on 2019-04-15.
//

#include "controller.h"
#include "action_interface/action.h"
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <cerrno>
#include <cstring>
#define STOP_CONDITION 0xFFFFFFFF


using namespace std;


controller::controller(action **tasks, size_t sizeTasks, unsigned int port, string ip_addr, int domain, int type, int protocol) {

    this->tasks = tasks;
    this->sizeTasks=sizeTasks;
    this->buffer=-1;


    if((socketHandle=socket(domain,type,protocol))<0)
        cout<<strerror(errno);


    address.sin_family = domain;
    inet_pton(domain,ip_addr.c_str(),&address.sin_addr);
    address.sin_port=htons(port);


    if((bind(socketHandle,(struct sockaddr *)&address,sizeof(address)))<0)
        cout<<strerror(errno);

}

controller::~controller() {

    if(shutdown(clientSocketHandle,SHUT_RDWR)<0)
        cout<<strerror(errno);

    if(shutdown(socketHandle,SHUT_RDWR)<0)
        cout<<strerror(errno);

}

void controller::takeAction() {

    for(int i=0;i<sizeTasks;i++)
        tasks[i]->takeAction(buffer);
}

void controller::run() {


    if(listen(socketHandle,1)<0)
        cout<<strerror(errno);



    if((clientSocketHandle=accept(socketHandle,(struct sockaddr*)&clientAddress,(socklen_t*)&clientAddressSize))<0)
        cout<<strerror(errno);


    do{

        if(recv(clientSocketHandle,&buffer,sizeof(int),0)>0)
            takeAction();

    }while(buffer!=STOP_CONDITION);
}