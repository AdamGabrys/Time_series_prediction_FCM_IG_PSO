#ifndef SUB_SWARM_H
#define SUB_SWARM_H
#include "Particle.h"
#include "Vel_pos.h"
#include <vector>

class Sub_swarm
{
    public:
        Sub_swarm(){_f=false;_best_Particle=Particle();_size=6;_particles.resize(_size);}//_particles=new Particle[4];};
        Sub_swarm(int part_per_sub_swarm, std::vector<Vel_pos>domain,std::vector<Vel_pos> u,int t,int c,bool f);
	Sub_swarm(Sub_swarm const& cpy){
		_f=cpy._f;
		_size=cpy._size;
		_best_Particle=cpy.get_best_particle_as_val();
		_particles=cpy._particles;
	}
        virtual ~Sub_swarm();
	Sub_swarm& operator=(Sub_swarm rhs){
		rhs.swap(*this);
		return *this;
	}
	void swap(Sub_swarm& s){
		std::swap(this->_f,s._f);
		std::swap(this->_size,s._size);
		std::swap(this->_particles,s._particles);
		std::swap(this->_best_Particle,s._best_Particle);
		std::cout<<"swap tablicy"<<std::endl;

	}
        Particle* get_particle(int i);
        Particle& get_best_particle();
        Particle get_best_particle_as_val()const{return _best_Particle;}
	std::vector<Particle> get_particles()const{return _particles;};
        int get_size()const;
        void set_best_particle(Particle* particle);

    protected:
    private:
	bool _f;
        int _size;
        Particle _best_Particle;
	std::vector<Particle> _particles;
};

#endif // SUB_SWARM_H
