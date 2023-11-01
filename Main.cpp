#include <iostream>
#include "Boost_Transmitter.h"
#include "Connection_Pool.h"


#ifdef CLIENT
#include "Boost_Client.h"
#endif

int main(){
    setlocale(LC_ALL, "rus");  

#ifdef CLIENT
    Boost_Client client;
    client.run();
#else
    Boost_Transmitter transmitter;
    transmitter.set_connection_manager(new Connection_Pool);
    transmitter.run();
#endif

    return 0;
}


