#include "rommcpp.h"

void Rommcpp::RomPool::runTui(){
    putMenu();
    int c {0};
    while (c == -1){
        std::cout << std::endl << "Invalid option. Please try again." << std::endl;
        putMenu();
    };
}