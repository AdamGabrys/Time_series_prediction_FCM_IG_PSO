#ifndef PARTICLE_H
#define PARTICLE_H
#include "Vel_pos.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include "sys/time.h"
#include "fit_func.h"
#include "fit_func_fcm.h"
#include <vector>

class Particle
{
    public:
        Particle(){_f=true;_arg=Vel_pos();Vel_pos _vel; Vel_pos _best_arg;_t=2;_c=5;_cur_fit=0;_best_fit=0;_domain.resize(2);_u.resize(2);}//_domain=new Vel_pos[2];_u=new Vel_pos[_t];}
        Particle(std::vector<Vel_pos> domain, std::vector<Vel_pos>  u,int t,int c, bool f);
        Particle(std::vector<Vel_pos> domain,std::vector<Vel_pos>  u,Vel_pos arg,int t,int c,bool f);

	Particle(Particle const & cpy){
		_f=cpy._f;
		_arg=cpy.get_arg();
		_vel=cpy.get_vel();
		_best_arg=cpy.get_best_fit_arg();
		_cur_fit=cpy.get_fit();
		_best_fit=cpy.get_best_fit();
		_t=cpy._t;
		_c=cpy._c;
		_domain=cpy._domain;
		_u=cpy._u;
	}

        virtual ~Particle();

	Particle& operator=(Particle rhs){rhs.swap(*this); return *this;}
         void swap(Particle& s)
         {
		/*this->f=s.f;
		this->_arg=s._arg;
		this->_vel=s._vel;
             this->_best_arg=s._best_arg;
	     this->_domain=s._domain;
	     this->_cur_fit=s._cur_fit;
	     this->_best_fit=s._best_fit;
	     this->_u=s._u;
	     this->_t=s._t;
	     this->_c=s._c;*/
	     std::swap(this->_f,s._f);
             std::swap(this->_arg,s._arg);
             std::swap(this->_vel ,s._vel);
             std::swap(this->_best_arg,s._best_arg);
	     std::swap(this->_domain,s._domain);
	     std::swap(this->_cur_fit,s._cur_fit);
	     std::swap(this->_best_fit,s._best_fit);
	     std::swap(this->_u,s._u);
	     std::swap(this->_t,s._t);
	     std::swap(this->_c,s._c);
         }

        void fit(Vel_pos v);
        Vel_pos get_arg()const{return _arg;}
        Vel_pos get_vel()const{return _vel;}
        Vel_pos get_best_fit_arg()const{return _best_arg;}
        std::vector<Vel_pos>  get_domain()const{return _domain;}
        std::vector<Vel_pos>  get_u()const{return _u;};
        int get_t()const{return _t;}
        int get_c()const{return _c;}
   	bool get_f()const{return _f;}
        double get_best_fit()const{return _best_fit;}
        double get_fit()const{return _cur_fit;}
        void set_vel(Vel_pos v){_vel=v;}
        Particle& operator=(const Particle* r){Particle par(r->get_domain(),r->get_u(),r->get_t(),r->get_c(),r->get_f());Particle& ret=par; return ret;}
    protected:
    private:
	bool _f;
        Vel_pos _arg, _vel, _best_arg;
        std::vector<Vel_pos> _domain;
        double _cur_fit, _best_fit;
        std::vector<Vel_pos> _u;
        int _t,_c;
};

#endif // PARTICLE_H
