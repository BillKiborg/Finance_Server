#include <iostream>
#include "Boost_Transmitter.h"

#include "Boost_Client.h"

int main(){
    setlocale(LC_ALL, "rus");    

#define CLIENT
#ifndef CLIENT
    Boost_Transmitter transmitter;
    transmitter.run();
#elif defined CLIENT
    Boost_Client client;
    client.run();
#endif

    return 0;
}


