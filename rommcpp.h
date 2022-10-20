#ifndef _ROMMCPP_H
#define _ROMMCPP_H
#include <iostream>
#include <string>
#include <map>
#include <vector>

namespace Rommcpp {
    class Menu;
    class Pool;
    class RomPool;
}

class Rommcpp::Menu {
public:
    int addOption(const std::string& name, const std::string& description);
    void listOptions();
private:
    std::vector<std::map<std::string, std::string>> options;
};

class Rommcpp::RomPool : public Rommcpp::Menu {

};

#endif // _ROMMCPP_H
