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

    for(size_t i=0; i<settings::stepNum;++i)
    {
        StepParticles(particles); 
    }

    return 0; 
}