#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>


//Returns an evenly distributed random number between zero and one
inline double Rand()noexcept
{
    return rand()/(double)(RAND_MAX); 
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

#endif