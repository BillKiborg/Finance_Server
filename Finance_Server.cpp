#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include "Boost_Transmitter.h"

int main(){
    setlocale(LC_ALL, "rus");

    Boost_Transmitter transmitter;
    transmitter.run();

    return 0;
}


