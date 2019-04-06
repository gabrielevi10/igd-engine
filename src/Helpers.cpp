#include "Helpers.h"

const std::vector<std::string> Helpers::Split(const std::string& s, const char& c) {    
    std::string buff{""};
    std::vector<std::string> v;

    for(char n : s) {
	    if (n != c) 
            buff+=n; 
        else
	        if (n == c && buff != "") { 
                v.push_back(buff); 
                buff = ""; 
            }
    }
	if(buff != "") 
    v.push_back(buff);
	
    return v;
}