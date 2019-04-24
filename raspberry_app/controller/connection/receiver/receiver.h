//
// Created by Piotr on 21.04.2019.
//

#ifndef ROBO1_RECEIVER_H
#define ROBO1_RECEIVER_H
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <exception>

using namespace std;


struct socketException: public exception{
    const char * what() const noexcept override {
        return "socket creation exception";
    }
};

struct bindException: public exception{
    const char * what() const noexcept override {
        return "bind socket exception";
    }
};

struct listenException: public exception{
    const char * what() const noexcept override {
        return "listen on socket exception";
    }
};

struct acceptException: public exception{
    const char * what() const noexcept override {
        return "accept client exception";
    }
};

struct shutdownException: public exception{
    const char * what() const noexcept override {
        return "shutdown socket exception";
    }
};


template <typename T, class B>
class receiver {
public:
    receiver(B *, void (B::*)(T),T,size_t ,int,string = "127.0.0.1",int = AF_INET,int = SOCK_STREAM,int = 0);
    ~receiver();
    void operator()();

private:

    B *obj;

    T stopCondition;
    void (B::*fun_ptr)(T);

    int socketHandle;
    struct sockaddr_in address;

    int clientSocketHandle;
    struct sockaddr_in clientAddress;
    size_t clientAddressSize;

    T * buffer;
    size_t bufferSize;
};

template <typename T,class B>
receiver<T,B>::receiver(B * obj, void (B::*fun)(T), T stopCondition, size_t bufferSize, int port, string ip_addr, int domain, int type, int protocol):fun_ptr(fun),stopCondition(stopCondition),obj(obj),bufferSize(bufferSize){

    buffer = new T[bufferSize];

    if((socketHandle=socket(domain,type,protocol))<0)
        throw socketException();

    address.sin_family = domain;
    inet_pton(domain,ip_addr.c_str(),&address.sin_addr);
    address.sin_port=htons(port);


    if((bind(socketHandle,(struct sockaddr *)&address,sizeof(address)))<0)
        throw bindException();
}

template <typename T, class B>
receiver<T,B>::~receiver() {

    if(shutdown(clientSocketHandle,SHUT_RDWR)<0)
        throw shutdownException();


    if(shutdown(socketHandle,SHUT_RDWR)<0)
        throw shutdownException();
}

template <typename T, class B>
void receiver<T,B>::operator()() {

    if (listen(socketHandle, 1) < 0)
        throw listenException();

    do {

        if ((clientSocketHandle = accept(socketHandle, (struct sockaddr *) &clientAddress, (socklen_t * ) & clientAddressSize)) < 0)
            throw acceptException();

        do {

            if (recv(clientSocketHandle, &buffer, sizeof(T)*bufferSize, MSG_WAITALL) > 0)
                (obj->*fun_ptr)(buffer);
            else
                break;

        } while (buffer != stopCondition);
    }while (buffer != stopCondition);
}


#endif //ROBO1_RECEIVER_H
