#include "Swarm.h"

Swarm::Swarm(std::vector<Vel_pos> domain,int sub_swarm_size,int part_num,std::vector<Vel_pos> u, int t, int c,bool f):_sub_swarm_size(sub_swarm_size)
{


    _domain=domain;
    _f=f;
    int part_per_sub_swarm=part_num/sub_swarm_size;
    for(int i=0; i<sub_swarm_size;i++)
        _sub_swarm.push_back(Sub_swarm(part_per_sub_swarm,domain,u, t, c, f));
    _best_particle=*_sub_swarm[0].get_particle(0);
    fit();
}

Swarm::~Swarm()
{
}


void Swarm::fit(){
    //wersja normalna
    Sub_swarm* sub_swarm;
    Particle* particle;
    for(int i=0; i<_sub_swarm_size;i++){
        sub_swarm=get_sub_swarm(i);
        for(int j=0; j<sub_swarm->get_size(); j++){
            particle=sub_swarm->get_particle(j);
            if(particle->get_best_fit()<_best_particle.get_best_fit())
                set_best_particle(particle);
            if(particle->get_best_fit()<sub_swarm->get_best_particle().get_best_fit())
                sub_swarm->set_best_particle(particle);
        }
    }
}

bool Swarm::is_in_domain(Vel_pos arg){
    for(int i=0; i<arg.get_size();i++){
        if(_domain[0][i]>=arg[i]||_domain[1][i]<=arg[i])
            return false;
    }
    return true;
}

Sub_swarm* Swarm::get_sub_swarm(int i){
    return &_sub_swarm[i];
}
