//
// Created by Piotr Kuglin on 2019-04-15.
//

#include "controller.h"
#include "action_interface/action.h"
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <bitset>
#define STOP_CONDITION 0xFFFFFFFF


using namespace std;


controller::controller(action **tasks, size_t sizeTasks, unsigned int port, string ip_addr, int domain, int type, int protocol) {

    this->tasks = tasks;
    this->sizeTasks=sizeTasks;
    this->buffer=-1;

    try {
        socketHandle=socket(domain,type,protocol);
    }catch (string &e) {
        cout<<"socket creation exception: "<<e<<endl;
    }

    address.sin_family = domain;
    inet_pton(domain,ip_addr.c_str(),&address.sin_addr);
    address.sin_port=htons(port);

    try{
        bind(socketHandle,(struct sockaddr *)&address,sizeof(address));
    }catch (string &e){
        cout<<"bind exception: "<<e<<endl;
    }
}

controller::~controller() {
    try {
        shutdown(clientSocketHandle,SHUT_RDWR);
        shutdown(socketHandle,SHUT_RDWR);
    }catch (string &e) {
        cout << "shutdown exception: " << e << endl;
    }
}

void controller::takeAction() {

    for(int i=0;i<sizeTasks;i++)
        tasks[i]->takeAction(buffer);
}

void controller::run() {

    try {
        listen(socketHandle,1);
    }catch (string &e){
        cout<<"listen exception: "<<e<<endl;
    }

    try{
        clientSocketHandle=accept(socketHandle,(struct sockaddr*)&clientAddress,(socklen_t*)&clientAddressSize);
    }catch (string &e){
        cout<<"accept exception: "<<e<<endl;
    }


    do{

        if(recv(clientSocketHandle,&buffer,sizeof(int),0)>0) {
            takeAction();
            std::bitset<32>a(buffer);
            cout<<a<<endl;
        }



    }while(buffer!=STOP_CONDITION); //TODO stop condition
}