#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>
#include <vector>

class Helpers {
    public:
        Helpers();
        static const std::vector<std::string> Split(const std::string& s, const char& c);    
};

#endif