#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_
#include "config.h"
#include <array>
#include "system.h"
#include <math.h>
#include <vector>
#include <fstream>


/*
    Text zeigt Anzahl Mittelungswerte in Python plot
*/

typedef std::array<std::vector<Point>,settings::particleNum> ParticleTracks; 
typedef std::array<Point,settings::particleNum> ParticleSet;

typedef std::array<double,settings::stepNum> TrackStatistic;
typedef std::vector<double> SquareLengthSet; 
ParticleSet GenerateParticles()
{
    ParticleSet ret; 
    
    for(size_t i=0; i<settings::particleNum;++i)
    ret.at(i)={Rand()*settings::width,Rand()*settings::height,Rand()*settings::length};

    return ret; 
}

inline SquareLengthSet CreateSquareLengthSet(const std::vector<Point>& points)noexcept
{
    SquareLengthSet ret; 
    for(size_t i=1; i<points.size();++i)
    ret.push_back(Squaredist(points.at(i),points.at(i-1)));

    return ret; 
}

/*batchSize=N of N*dt*/
inline double MeanSquareBatch(const SquareLengthSet& squareLengths, size_t batchSize)noexcept
{
    long double sumTrack=0;
    long double sumBatch=0;
    for(size_t i=0; i<squareLengths.size()-batchSize;++i)
    {
    for(size_t j=0; j<batchSize;++j)
    {
        sumBatch+=squareLengths.at(i+j);
    }
    sumTrack+=sumBatch;
    sumBatch=0;
    }
    return sumTrack/((squareLengths.size()-batchSize));
}

inline TrackStatistic CreateStatistic(const ParticleTracks& listParticles)noexcept
{
    TrackStatistic ret={0}; 

    for(size_t trackId=0; trackId<listParticles.size();++trackId)
    {
    const SquareLengthSet squareLengthSet=CreateSquareLengthSet(listParticles.at(trackId));
    for(size_t i=0; i<settings::stepNum-2;++i)
    {
        ret.at(i)+=MeanSquareBatch(squareLengthSet,i+1)/listParticles.size();
    }
    }
    


    return ret; 
}
inline void StepParticles(ParticleSet& particles, ParticleTracks& listParticles)noexcept
{
    static Point driftStep; 
    driftStep=driftStep+settings::driftVelocity*settings::deltaTime;
    for(size_t i=0; i<particles.size();++i)
    {
        auto& particle=particles.at(i);
        //randomizing traveling distance and direction in spherical coordinate space
        const double azimuth=2*settings::pi*Rand();
        const double polar=settings::pi*Rand();
        /*
        ----------------
        Gauß <-> BITTE
        Kleine Halbwertsbreite 
        ----------------
        */
        const double radius=settings::stepLength*2*Rand();
        //mapping to cartesian coordinates
        const Point step{radius*sin(polar)*cos(azimuth),radius*sin(polar)*sin(azimuth),radius*cos(polar)};
        particle=particle+step+driftStep;
        listParticles.at(i).push_back(particle);
    }
}

inline void SaveTracks(const ParticleTracks& tracks, const std::string& path)noexcept
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
inline void SaveStatistic(const TrackStatistic& statistic,const std::string& path)noexcept
{ 
    std::ofstream File{path,std::ios::binary|std::ios::trunc};
    File<<"//Statisticical measure of random walk\n//deltaTime: "
    <<settings::deltaTime<<
    "\n//imageSeries: "<<settings::stepNum<<
    "\n//driftVelocity (x,y,z): "<<settings::driftVelocity.x<<" "<<settings::driftVelocity.y<<" "<<settings::driftVelocity.z
    <<"\n//dimensions (w,h,l): "<<settings::width<<" "<<settings::height<<" "<<settings::length<<"\n";
    File<<"//dt*n : <dr^2>\n";
    for(size_t i=0; i<statistic.size()-2;++i)
    File<<(i+1)*settings::deltaTime<<" : "<<statistic.at(i)<<"\n";
    
    

    File.close();
}

#endif