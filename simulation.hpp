#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_
#include "config.hpp"
#include <array>
#include "system.hpp"
#include <math.h>

std::array<Point,settings::particleNum> GenerateParticles()
{
    std::array<Point,settings::particleNum> ret; 
    
    for(size_t i=0; i<settings::particleNum;++i)
    ret.at(i)={Rand()*settings::width,Rand()*settings::height,Rand()*settings::length};

    return ret; 
}

inline void StepParticles(std::array<Point,settings::particleNum>& particles)noexcept
{
    for(auto &particle:particles)
    {
        //randomizing traveling distance and direction in spherical coordinate space
        const double azimuth=2*settings::pi*Rand();
        const double polar=settings::pi*Rand();
        const double radius=sqrt(settings::stepSizeSqu*(2*Rand()-1));
        //mapping to cartesian coordinates
        const Point step{radius*sin(polar)*cos(azimuth),radius*sin(polar)*sin(azimuth),radius*cos(polar)};
        //updating particle position
        particle=particle+step+settings::driftStep; 
    }
}


#endif