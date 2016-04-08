#include "Pso.h"

Pso::Pso(int seCyNum,int meCyNum, double omega,double c1,double c2,double c3,std::vector<Vel_pos>domain,int sub_swarm_size, int part_num,std::vector<Vel_pos> u, int t, int c, bool f):
    _se_cy_num(seCyNum), _me_cy_num(meCyNum),_omega(omega),_c1(c1),_c2(c2),_c3(c3),mud_slow(1.0/1.2)
{//std::cout<<"zaczynam konstruktor PSO"<<std::endl;
    _it_num=0;
    _u=u;
    _f=f;
    _swarm=Swarm(domain,sub_swarm_size,part_num,u,t,c,f);
    _swarm.fit();
//std::cout<<"koncze konstruktor PSO"<<std::endl;
}

Pso::~Pso()
{
}
double Pso::get_best_fit(){
    return _swarm.get_best_particle().get_best_fit();
}
Vel_pos Pso::get_best_fit_arg(){
    return _swarm.get_best_particle_as_cp().get_best_fit_arg();
}

int Pso::get_it_num(){
    return _it_num;
}

void Pso::do_next_it(){
    for(int i=0; i<_me_cy_num; i++)
        _do_me();
    for(int i=0; i<_se_cy_num; i++)
        _do_se();
    _it_num++;
    //std::cout<<"najlepiej dopasowana:  fit: "<<_swarm.get_best_particle().get_best_fit()<<std::endl;
}

void Pso::_do_se(){
    Sub_swarm* sub_swarm;
    Particle* particle;
    for(int i=0; i<_swarm.get_sub_swarm_size();i++){
        sub_swarm=_swarm.get_sub_swarm(i);//ZWRACAC REFERENCJE
        for(int j=0; j<sub_swarm->get_size(); j++){
            particle=sub_swarm->get_particle(j);//ZWRACAC REFERENCJE
            while(true){
                double r1=(double)rand()/(double)RAND_MAX;
                double r2=(double)rand()/(double)RAND_MAX;
                double r3=(double)rand()/(double)RAND_MAX;
                Vel_pos v=_omega*particle->get_vel()+(_c1*r1*(particle->get_best_fit_arg()-particle->get_arg()))+(_c2*r2*(sub_swarm->get_best_particle().get_best_fit_arg()-particle->get_arg()))+(_c3*r3*(_swarm.get_best_particle().get_best_fit_arg()-particle->get_arg()));
                if(_swarm.is_in_domain(particle->get_arg()+v)){//std::cout<<"weszlem a nie widzisz"<<std::endl;
                    particle->fit(v);//zmienic wszystko, fit moze zajac sie zmiana parametrow
                    break;
                }
                else{
                    particle->set_vel(mud_slow*particle->get_vel());
                }
            }
        }
    }
    _swarm.fit();
}
void Pso::_do_me(){
    Sub_swarm* sub_swarm;
    Particle* particle;
    for(int i=0; i<_swarm.get_sub_swarm_size();i++){
        sub_swarm=_swarm.get_sub_swarm(i);//ZWRACAC REFERENCJE
        for(int j=0; j<sub_swarm->get_size(); j++){
            particle=sub_swarm->get_particle(j);//ZWRACAC REFERENCJE
            while(true){
                double r1=(double)rand()/(double)RAND_MAX;
                double r2=(double)rand()/(double)RAND_MAX;
                Vel_pos v=_omega*particle->get_vel()+(_c1*r1*(particle->get_best_fit_arg()-particle->get_arg()))+(_c2*r2*(sub_swarm->get_best_particle().get_best_fit_arg()-particle->get_arg()));//jed
                if(_swarm.is_in_domain(particle->get_arg()+v)){//std::cout<<"dzialam"<<std::endl;//std::cout<<"weszlem a nie widzisz"<<std::endl;
                    particle->fit(v);//zmienic wszystko, fit moze zajac sie zmiana parametrow
                    break;
                }
                else{
                    particle->set_vel(mud_slow*particle->get_vel());
                }
            }
        }
    }
    _swarm.fit();
}
