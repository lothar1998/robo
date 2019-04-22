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

template <typename T>
receiver<T>::receiver(void (*fun)(T), T stopCondition, int port, string ip_addr, int domain, int type, int protocol):fun_ptr(fun),stopCondition(stopCondition),socketHandle(0),clientAddress(0),clientAddressSize(0),clientSocketHandle(0) {

    if((socketHandle=socket(domain,type,protocol))<0)
        cout<<strerror(errno);


    address.sin_family = domain;
    inet_pton(domain,ip_addr.c_str(),&address.sin_addr);
    address.sin_port=htons(port);


    if((bind(socketHandle,(struct sockaddr *)&address,sizeof(address)))<0)
        cout<<strerror(errno);
}

template <typename T>
receiver<T>::~receiver() {
    if(shutdown(clientSocketHandle,SHUT_RDWR)<0)
        cout<<strerror(errno);

    if(shutdown(socketHandle,SHUT_RDWR)<0)
        cout<<strerror(errno);
}

template <typename T>
void receiver<T>::operator()() {

    if(listen(socketHandle,1)<0)
        cout<<strerror(errno);



    if((clientSocketHandle=accept(socketHandle,(struct sockaddr*)&clientAddress,(socklen_t*)&clientAddressSize))<0)
        cout<<strerror(errno);

    do{

        if(recv(clientSocketHandle,&buffer,sizeof(T),0)>0)
            fun_ptr(buffer);

    }while(buffer!=stopCondition);
}