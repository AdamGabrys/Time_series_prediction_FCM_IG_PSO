#ifndef SWARM_H
#define SWARM_H
#include "Sub_swarm.h"
#include "Particle.h"
#include "Vel_pos.h"

class Swarm
{
    public:
        Swarm(){_f=false;_best_particle=Particle();_sub_swarm_size=3;_sub_swarm.resize(_sub_swarm_size);_domain.resize(2);} //_sub_swarm=new Sub_swarm[2]; _domain=new Vel_pos[2];}
        Swarm(std::vector<Vel_pos>domain,int sub_swarm_size,int part_num,std::vector<Vel_pos> u, int t, int c,bool f);
	Swarm(Swarm const& cpy){
		_f=cpy._f;
		_best_particle=cpy.get_best_particle_as_cp();
		_sub_swarm=cpy._sub_swarm;
		_sub_swarm_size=cpy._sub_swarm_size;
		_domain=cpy._domain;
	}
        virtual ~Swarm();
	Swarm& operator=(Swarm rsh){
		rsh.swap(*this);
		return *this;
	}
	void swap(Swarm &s){
		std::swap(this->_f,s._f);
		std::swap(this->_best_particle,s._best_particle);
		std::swap(this->_sub_swarm,s._sub_swarm);
		std::swap(this->_sub_swarm_size,s._sub_swarm_size);
		std::swap(this->_domain,s._domain);
	}
        bool is_in_domain(Vel_pos arg);
        void fit();
        Sub_swarm* get_sub_swarm(int i);
        Particle& get_best_particle(){return _best_particle;}
	Particle get_best_particle_as_cp()const{return _best_particle;}
        int get_sub_swarm_size(){return _sub_swarm_size;}
        void set_best_particle(Particle* particle){_best_particle=*particle;}
    protected:
    private:
        Particle _best_particle;
        std::vector<Sub_swarm> _sub_swarm;
        int _sub_swarm_size;
        std::vector<Vel_pos> _domain;
	bool _f;
};

#endif // SWARM_H
