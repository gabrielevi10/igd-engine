#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>
#include <vector>

#include "Vec2.h"

class Helpers {
    public:
        Helpers();
        static const std::vector<std::string> Split(const std::string& s, const char& c);
        static double ConvertToRadians(double angle);
        static double ConvertToDegree(double angle);   
        static double AngleBetweenTwoPoints(Vec2 v0, Vec2 v1);
        static double EuclideanDistance(Vec2 v0, Vec2 v1);
};

#endif