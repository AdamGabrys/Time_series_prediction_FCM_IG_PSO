#include "Sub_swarm.h"

Sub_swarm::Sub_swarm(int part_per_sub_swarm, std::vector<Vel_pos> domain,std::vector<Vel_pos> u,int t,int c, bool f):_size(part_per_sub_swarm)
{
    _f=f;
    for(int i=0; i<part_per_sub_swarm;i++)
        _particles.push_back(Particle(domain,u,t,c,f));
    _best_Particle=_particles[0];
}

Sub_swarm::~Sub_swarm()
{

}

Particle& Sub_swarm::get_best_particle(){
    return _best_Particle;
}
Particle* Sub_swarm::get_particle(int i){
    return &_particles[i];
}

int Sub_swarm::get_size()const{
    return _size;
}
void Sub_swarm::set_best_particle(Particle* particle){
    _best_Particle=*particle;
}
