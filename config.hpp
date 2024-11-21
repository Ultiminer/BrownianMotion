#ifndef CONFIG_HPP_
#define CONFIG_HPP_
#include <cstdint> 
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
CONSTa width{1e4};//width in micrometer
CONSTa height{1e4};//height in micrometer
CONSTa length{1e3};//length in micrometer
CONSTa deltaTime{1};//deltaTime in milliseconds
CONST Point driftStep{1,1,1};//how many micrometers you wanna step 
CONSTa numArguments{1};
CONSTa viscosity{10};//viscosity in mircometer^2
CONSTa boltzmann{10};//boltzmann in micrometer
CONSTa beadSize{1}; //beadSize in micrometer
CONSTa beadRadius{beadSize/2.0}; //beadSize in micrometer
CONSTa temperature{300};//temperature in Kelvin
CONSTa pi{3.141592653589793238};
CONSTa dimensions{3}; 
CONSTa diffusion{boltzmann*temperature/(6*pi*viscosity*beadRadius)};
CONSTa stepSizeSqu{2*dimensions*diffusion*deltaTime};
CONSTa stepNum{300};
};


#endif