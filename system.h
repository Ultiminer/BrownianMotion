#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <random>

typedef std::mt19937 rng_type;
std::uniform_int_distribution<rng_type::result_type> udist(0, RAND_MAX);

rng_type rng;

//Returns an evenly distributed random number between zero and one
inline double Rand()noexcept
{
  rng_type::result_type random_number = udist(rng);
  return (double)random_number/(double)(RAND_MAX); 
}


inline void Print(std::string str)noexcept
{
    printf(str.c_str()); 
}
inline std::string PrintRet(std::string str)noexcept
{
    printf(str.c_str()); 
    printf("\n");
    return str;
}
inline void Print(const char* str)noexcept
{
    printf(str); 
}
inline void Print(float str)noexcept
{
    printf("%f",str); 
}
inline void Print(int str)noexcept
{
    printf("%i",str); 
}
inline void Print(double str)noexcept
{
    printf("%lf",str); 
}
template<typename ...Args>
inline void Print(Args... args)noexcept
{
    printf(args...);
}

inline std::string input(const char* msg)noexcept
{
    printf(msg); 
    std::string line;
    std::getline(std::cin,line);

    return line; 
}
template<typename T>
inline void fun_assert(int condition, int line, const char* fileStr, T msg)noexcept
{
    if(condition)return;
    printf("assert triggered on line %i in file %s \n",line,fileStr);
    Print(msg);
    exit(EXIT_FAILURE);
}

#define assert(x) fun_assert((x), __LINE__,__FILE__,"")
#define assert_msg(x,msg) fun_assert((x), __LINE__,__FILE__,(msg))
struct Point{
double x;
double y; 
double z; 
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

#endif