//
// Created by Piotr Kuglin on 2019-04-15.
//

#ifndef ROBO1_CONTROLLER_H
#define ROBO1_CONTROLLER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include "raspberry_app/action_interface/setAction.h"

class controller {
public:
    controller(setAction **,size_t,unsigned int, std::string = "127.0.0.1", int = AF_INET,int = SOCK_STREAM,int = 0);

    void operator()();


private:

    void takeAction(int);

    setAction ** tasks;
    size_t sizeTasks;

    unsigned int port;
    std::string ip_addr;
    int domain;
    int type;
    int protocol;


};


#endif //ROBO1_CONTROLLER_H
