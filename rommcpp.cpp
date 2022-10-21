#include "rommcpp.h"

void addOptions(Rommcpp::RomPool& romPool){
    std::vector<std::map<std::string, std::string>> options{
        {{"Set ROM directory", "Set the directory where your ROMs are stored"}},
        {{"List ROMs", "List all the ROMs in the ROM directory"}},
        {{"Add ROM", "Add a ROM to the ROM directory"}},
        {{"Remove ROM", "Remove a ROM from the ROM directory"}},
        {{"Exit", "Exit the program"}}};
    for (const auto& option : options){
        for (const auto& item : option){
            romPool.addOption(item.first, item.second);
        }
    }
}

void configureMenu(Rommcpp::RomPool& romPool){
    romPool.setTitle("Rommcpp");
    romPool.setSubtitle("A ROM manager written in C++");
    addOptions(romPool);
}

int main(){
    Rommcpp::RomPool romPool;
    configureMenu(romPool);
    romPool.runTui();
    return 0;
}
