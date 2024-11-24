#include "system.h"
#include "config.h"
#include "simulation.h"
#include <time.h>

int main(int argc, char** argv)
{
    //Handling of standard input
    assert(argc==settings::numArguments);
    const char* mainPath=argv[0];
    //Seeds the random function with current time in seconds
    rng.seed(time(NULL)%10000);
    ParticleSet particles=GenerateParticles();
    ParticleTracks tracks;
    for(size_t i=0; i<settings::stepNum;++i)
    {
        StepParticles(particles,tracks); 
    }
    TrackStatistic stats=CreateStatistic(tracks);

    SaveStatistic(stats,"stats.txt"); 
    SaveTracks(tracks,"tracks");
    return 0; 
}