#ifndef _ROMMCPP_H
#define _ROMMCPP_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

namespace Rommcpp {
    class Menu;
    class Pool;
    class RomPool;
}

class Rommcpp::Menu {
public:
    int addOption(const std::string& name, const std::string& description);
    void listOptions();
    int getOptionIndex(const std::string& name);
    void setTitle(const std::string& title);
    void setSubtitle(const std::string& subtitle);
    void putMenu();
    void putLine(int length);
    int getOptionCount();
    int askUserForOption();
private:
    std::vector<std::map<std::string, std::string>> options;
    std::string title;
    std::string subtitle;
    int lastSuccessfulChoice;
    int lastChoice;
};

class Rommcpp::RomPool : public Rommcpp::Menu {
public:
    void runTui();
};

#endif // _ROMMCPP_H
