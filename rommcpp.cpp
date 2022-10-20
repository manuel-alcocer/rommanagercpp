#include "rommcpp.h"

void addOptions(Rommcpp::RomPool& romPool){
    std::map<std::string, std::string> options{
        {"Set ROM directory", "Set the directory where your ROMs are stored"},
        {"List ROMs", "List all the ROMs in the ROM directory"},
        {"Add ROM", "Add a ROM to the ROM directory"},
        {"Remove ROM", "Remove a ROM from the ROM directory"},
        {"Exit", "Exit the program"}
    };
    for (const auto& [name, description] : options){
        std::cout << romPool.addOption(name, description) << std::endl;
    }
}

int main(){
    Rommcpp::RomPool romPool;
    addOptions(romPool);
    romPool.listOptions();
    return 0;
}
