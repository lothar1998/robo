//
// Created by Piotr on 21.04.2019.
//

#ifndef ROBO1_RECEIVER_H
#define ROBO1_RECEIVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>


using namespace std;

template <typename T, class B>
class receiver {
public:
    receiver(B *, void (B::*)(T),T,int,string = "127.0.0.1",int = AF_INET,int = SOCK_STREAM,int = 0);
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

    T buffer;//TODO maybe array or something
};


#endif //ROBO1_RECEIVER_H
