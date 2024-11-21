#include "system.hpp"
#include "config.hpp"
#include "simulation.hpp"
#include <time.h>

int main(int argc, char** argv)
{
    assert(argc==settings::numArguments);
    const char* mainPath=argv[0];
    srand(time(NULL));

    auto particles=GenerateParticles();
    ParticleTracks tracks;
    for(size_t i=0; i<settings::stepNum;++i)
    {
        StepParticles(particles,tracks); 
    }
    SaveTracks(tracks,"tracks");
    return 0; 
}