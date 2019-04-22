//
// Created by Piotr on 21.04.2019.
//

#ifndef ROBO1_RECEIVER_H
#define ROBO1_RECEIVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include "raspberry_app/controller/controller.h"

using namespace std;


class receiver {
public:
    receiver(controller *, void (controller::*)(int),int,int,string = "127.0.0.1",int = AF_INET,int = SOCK_STREAM,int = 0);
    ~receiver();
    void operator()();

private:

    controller *obj;

    int stopCondition;
    void (controller::*fun_ptr)(int);

    int socketHandle;
    struct sockaddr_in address;

    int clientSocketHandle;
    struct sockaddr_in clientAddress;
    size_t clientAddressSize;

    int buffer;//TODO maybe array or something
};


#endif //ROBO1_RECEIVER_H
