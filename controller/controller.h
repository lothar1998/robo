//
// Created by Piotr Kuglin on 2019-04-15.
//

#ifndef ROBO1_CONTROLLER_H
#define ROBO1_CONTROLLER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include "servos/servo.h"
#include "action_interface/action.h"

class controller {
public:
    controller(action **,size_t,unsigned int, std::string = "127.0.0.1", int = AF_INET,int = SOCK_STREAM,int = 0);
    ~controller();

    void run();


private:


    action ** tasks;
    size_t sizeTasks;

    int socketHandle;
    struct sockaddr_in address;

    int clientSocketHandle;
    struct sockaddr_in clientAddress;
    size_t clientAddressSize;

    int buffer;

    int * readMessage();
    void takeAction();


};


#endif //ROBO1_CONTROLLER_H
