#ifndef CONFIG_HPP_
#define CONFIG_HPP_
#include <cstdint> 
#include <math.h>
#include "system.h"
#define CONSTa inline constexpr auto
#define CONST inline constexpr 

namespace settings
{
CONSTa numArguments{1};
CONSTa pi{3.14159265358979};
CONSTa particleNum{100};
CONSTa width{200};//width in micrometer
CONSTa height{200};//height in micrometer
CONSTa length{100};//length in micrometer
CONSTa deltaTime{1};//deltaTime in seconds
CONST Point driftVelocity{0,0,0};//how many micrometers you wanna step 
inline double stepLength{1};
CONST size_t stepNum{50};

};


#endif