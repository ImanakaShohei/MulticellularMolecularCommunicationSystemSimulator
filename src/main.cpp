#include "SimMain.hpp"
#include <exception>
#include <iostream>

int main(int argc, char** argv)
{
    try {
        return SimMain::Run(argc, argv);
    }
    catch (::std::exception& e) {
        ::std::cerr << "Exception occured." << ::std::endl;
        ::std::cerr << e.what() << ::std::endl;
        return 1;
    }
    
}