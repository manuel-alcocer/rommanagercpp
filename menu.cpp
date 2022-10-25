#include "rommcpp.h"

int Rommcpp::Menu::addOption(const std::string& name, const std::string& description){
    options.push_back({{name, description}});
    return options.size()-1;
}

void Rommcpp::Menu::listOptions(){
    for (const auto& option : options){
        for (const auto& item : option){
            std::cout <<
            getOptionIndex(item.first) << " ...... "
            << item.first << ":" << std::endl <<
            "           " << item.second << "." << std::endl <<std::endl;
        }
    }
}

int Rommcpp::Menu::getOptionIndex(const std::string& name){
    for (int i = 0; i < options.size(); i++){
        for (const auto& item : options[i]){
            if (item.first == name){
                return i;
            }
        }
    }
    return -1;
}

void Rommcpp::Menu::setTitle(const std::string& title){
    this->title = title;
}

void Rommcpp::Menu::setSubtitle(const std::string& subtitle){
    this->subtitle = subtitle;
}

void Rommcpp::Menu::putMenu(){
    std::cout << std::endl;
    if (title != ""){
        std::cout << title << std::endl;
    }
    if (subtitle != ""){
        putLine(subtitle.length() > title.length() ? subtitle.length() : title.length());
        std::cout << subtitle << std::endl;
    }
    std::cout << std::endl;
    listOptions();
}

void Rommcpp::Menu::putLine(int length){
    for (int i = 0; i < length; i++){
        std::cout << "-";
    }
    std::cout << std::endl;
}

int Rommcpp::Menu::getOptionCount(){
    return options.size();
}

int Rommcpp::Menu::askUserForOption(){
    std::string input;
    std::cout << "Enter your choice: ";
    std::cin >> input;
    std::stringstream ss(input);
    ss >> lastChoice;
    if (ss.fail()){
        return -1;
    }
    lastSuccessfulChoice = lastChoice;
    return lastChoice;
}