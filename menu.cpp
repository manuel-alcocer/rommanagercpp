#include "rommcpp.h"

int Rommcpp::Menu::addOption(const std::string& name, const std::string& description){
    options.push_back({{name, description}});
    return options.size()-1;
}

void Rommcpp::Menu::listOptions(){
}
