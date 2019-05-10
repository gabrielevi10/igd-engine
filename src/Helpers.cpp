#include "Helpers.h"
#include "Vec2.h"
#include <cmath>

#define PI 3.14159265359

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

double Helpers::ConvertToRadians(double angle) {
    return (angle*PI)/180;
}

double Helpers::ConvertToDegree(double angle) {
    return (angle*180)/PI;
}

double Helpers::AngleBetweenTwoPoints(Vec2 v0, Vec2 v1) {
    return atan2(v1.y - v0.y, v1.x - v0.x);
}

double Helpers::EuclideanDistance(Vec2 v0, Vec2 v1) {
    return sqrt(pow(v0.x - v1.x, 2) + pow(v1.y - v1.y, 2));
}