#ifndef CONFIG_HPP_
#define CONFIG_HPP_
#include <cstdint> 
#include <math.h>

#define CONSTa inline constexpr auto
#define CONST inline constexpr 
struct Point{
double x;
double y; 
double z; 
};
struct KinPoint
{
Point pos; 
Point vel; 
};
constexpr int operator==(const Point& a, const Point& b)noexcept
{
    return (a.x==b.x)&&(a.y==b.y)&&(a.z==b.z);
}
constexpr Point operator+(const Point& a, const Point& b)noexcept
{
    return {a.x+b.x,a.y+b.y,a.z+b.z};
}
constexpr Point operator-(const Point& a, const Point& b)noexcept
{
    return {a.x-b.x,a.y-b.y,a.z-b.z};
}
constexpr double operator*(const Point& a, const Point& b)noexcept
{
    return a.x*b.x+a.y*b.y+a.z*b.z;
}
constexpr Point operator*(const Point& a, const double x)noexcept
{
    return {a.x*x,a.y*x,a.z*x};
}
constexpr Point operator*(const double x,const Point& a)noexcept
{
    return {a.x*x,a.y*x,a.z*x};
}
constexpr double Squaredist(const Point& a, const Point& b)noexcept
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z); 
}

namespace settings
{
CONSTa particleNum{100};
CONSTa width{200};//width in micrometer
CONSTa height{200};//height in micrometer
CONSTa length{100};//length in micrometer
CONSTa deltaTime{1};//deltaTime in seconds
CONST Point driftVelocity{4,4,4};
CONST Point driftStep{driftVelocity*deltaTime};//how many micrometers you wanna step 
CONSTa numArguments{1};
CONSTa beadSize{1}; //beadSize in micrometer
CONSTa beadRadius{beadSize/2.0}; //beadSize in micrometer
CONSTa temperature{300};//temperature in Kelvin
CONSTa pi{3.14159265358979};
CONSTa dimensions{3}; 
CONSTa diffusion{0.9};
CONSTa stepSizeSqu{2*dimensions*diffusion*deltaTime};
inline double stepSize{sqrt(stepSizeSqu)};
CONSTa stepNum{10};

};


#endif