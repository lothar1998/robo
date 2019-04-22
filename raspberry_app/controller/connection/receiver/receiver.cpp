//
// Created by Piotr on 21.04.2019.
//

#include "receiver.h"
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>


receiver::receiver(controller * obj, void (controller::*fun)(int), int stopCondition, int port, string ip_addr, int domain, int type, int protocol):fun_ptr(fun),stopCondition(stopCondition),obj(obj){

    if((socketHandle=socket(domain,type,protocol))<0)
        cout<<strerror(errno);


    address.sin_family = domain;
    inet_pton(domain,ip_addr.c_str(),&address.sin_addr);
    address.sin_port=htons(port);


    if((bind(socketHandle,(struct sockaddr *)&address,sizeof(address)))<0)
        cout<<strerror(errno);
}

receiver::~receiver() {
    if(shutdown(clientSocketHandle,SHUT_RDWR)<0)
        cout<<strerror(errno);

    if(shutdown(socketHandle,SHUT_RDWR)<0)
        cout<<strerror(errno);
}


void receiver::operator()() {

    if(listen(socketHandle,1)<0)
        cout<<strerror(errno);



    if((clientSocketHandle=accept(socketHandle,(struct sockaddr*)&clientAddress,(socklen_t*)&clientAddressSize))<0)
        cout<<strerror(errno);

    cout<<"accepted"<<endl;

    do{

        if(recv(clientSocketHandle,&buffer,sizeof(int),0)>0)
            (obj->*fun_ptr)(buffer);

    }while(buffer!=stopCondition);

    cout<<"ended"<<endl;
}