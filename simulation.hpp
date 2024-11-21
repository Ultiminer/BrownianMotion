#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_
#include "config.hpp"
#include <array>
#include "system.hpp"
#include <math.h>
#include <vector>
#include <fstream>

typedef std::array<std::vector<Point>,settings::particleNum> ParticleTracks; 
typedef std::array<Point,settings::particleNum> ParticleSet;


ParticleSet GenerateParticles()
{
    ParticleSet ret; 
    
    for(size_t i=0; i<settings::particleNum;++i)
    ret.at(i)={Rand()*settings::width,Rand()*settings::height,Rand()*settings::length};

    return ret; 
}


inline void StepParticles(ParticleSet& particles, ParticleTracks& listParticles)noexcept
{
    for(size_t i=0; i<particles.size();++i)
    {
        auto& particle=particles.at(i);
        //randomizing traveling distance and direction in spherical coordinate space
        const double azimuth=2*settings::pi*Rand();
        const double polar=settings::pi*Rand();
        const double radius=settings::stepSize*2*Rand();
        //mapping to cartesian coordinates
        const Point step{radius*sin(polar)*cos(azimuth),radius*sin(polar)*sin(azimuth),radius*cos(polar)};
        //updating particle position
        particle=particle+step+settings::driftStep;
        listParticles.at(i).push_back(particle);
    }
}

inline void SaveTracks(const ParticleTracks& tracks, std::string path)noexcept
{
    std::ofstream File(path+"3d",std::ios::trunc|std::ios::binary);
    for(auto& particle:tracks)
    {
        for(size_t i=0; i<particle.size()-1;++i)File<<particle.at(i).x<<" "<<particle.at(i).y<<" "<<particle.at(i).z<<" ";
        if(particle.size())
        File<<particle.back().x<<" "<<particle.back().y<<" "<<particle.back().z;
        File<<"\n";
    }
    
    File.close();
    File.open(path+"2d",std::ios::trunc|std::ios::binary);
    for(auto& particle:tracks)
    {
        for(size_t i=0; i<particle.size()-1;++i)File<<particle.at(i).x<<" "<<particle.at(i).y<<" ";
        if(particle.size())
        File<<particle.back().x<<" "<<particle.back().y;
        File<<"\n";
    }
    
    File.close();
    File.open(path+"1d",std::ios::trunc|std::ios::binary);
    for(auto& particle:tracks)
    {
        for(size_t i=0; i<particle.size()-1;++i)File<<particle.at(i).x<<" ";
        if(particle.size())
        File<<particle.back().x;
        File<<"\n";
    }
    
    File.close();
}
#endif