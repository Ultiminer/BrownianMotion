#include "system.hpp"
#include "config.hpp"
#include "simulation.hpp"
#include <time.h>

int main(int argc, char** argv)
{
    //Handling of standard input
    assert(argc==settings::numArguments);
    const char* mainPath=argv[0];

    //Seeds the random function with current time in seconds
    srand(time(NULL));

    ParticleSet particles=GenerateParticles();
    ParticleTracks tracks;
    for(size_t i=0; i<settings::stepNum;++i)
    {
        StepParticles(particles,tracks); 
    }
    SaveTracks(tracks,"tracks");
    return 0; 
}