#include <iostream>
#include "Boost_Transmitter.h"
#include "Connection_Pool.h"


int main(){
    setlocale(LC_ALL, "rus");    

    Boost_Transmitter transmitter;
    transmitter.set_connection_manager(new Connection_Pool);
    transmitter.run();

    return 0;
}


