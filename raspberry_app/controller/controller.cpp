//
// Created by Piotr Kuglin on 2019-04-15.
//

#include "controller.h"
#include "raspberry_app/action_interface/action.h"
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <thread>
#include "raspberry_app/controller/connection/receiver/receiver.h"
#define STOP_CONDITION 0xFFFFFFFF


using namespace std;


controller::controller(action **tasks, size_t sizeTasks, unsigned int port, string ip_addr, int domain, int type, int protocol):tasks(tasks),sizeTasks(sizeTasks),port(port),ip_addr(ip_addr),domain(domain),type(type),protocol(protocol) {

}

controller::~controller() {



}

void controller::operator()(){

    receiver<int,controller> recv(this,&controller::takeAction,(int)STOP_CONDITION,port,ip_addr,domain,type,protocol);
    thread threadReceive(std::ref(recv));
    threadReceive.join();
    cout<<"joined"<<endl;
}

void controller::takeAction(int command) {

    cout<<"inside action: "<<command<<endl;
    cout<<"sizeTask: "<<sizeTasks<<endl;
    for(int i=0;i<sizeTasks;i++)
        (this->tasks)[i]->takeAction(command);

}