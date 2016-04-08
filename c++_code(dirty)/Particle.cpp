#include "Particle.h"

Particle::Particle(std::vector<Vel_pos> domain, std::vector<Vel_pos> u,int t,int c,bool f):_t(t),_c(c)
{
    _u=u;
    _domain=domain;
     _f=f;
    int size=_domain[0].get_size();
    double* arg_tab=new double[size];
    for (int i=0; i<size; i++){
        arg_tab[i]=((double)rand()/(double)RAND_MAX)*(domain[1][i]-domain[0][i])+domain[0][i];
    }
    _arg=Vel_pos(arg_tab,size);
    _vel=Vel_pos(0.0,size);
    if(f==false)
    	_cur_fit=fit_func(_u,_t,_c,_arg);
    if(f==true)
	_cur_fit=fit_func_fcm(_u,_t,_c,_arg);
    _best_fit=_cur_fit;
    _best_arg=_arg;
    delete [] arg_tab;
}

Particle::Particle(std::vector<Vel_pos>  domain,std::vector<Vel_pos>  u, Vel_pos arg,int t,int c,bool f):_arg(arg),_best_arg(arg),_t(t),_c(c)
{
    _domain=domain;
    _u=u;
    _f=f;
    int size=domain[0].get_size();
    _vel=Vel_pos(0.0,size);
    _cur_fit=0;
    _best_fit=0;
}

Particle::~Particle()
{

}

void Particle::fit(Vel_pos v){
    _vel=v;
    _arg=_arg+v;
    if(_f==false){
    	_cur_fit=fit_func(_u,_t,_c,_arg);
    	if(_cur_fit<=_best_fit){
        	_best_fit=_cur_fit;
        	_best_arg=_arg;
    	}
    }
    if(_f==true){
    	_cur_fit=fit_func_fcm(_u,_t,_c,_arg);
    	if(_cur_fit<=_best_fit){
        	_best_fit=_cur_fit;
        	_best_arg=_arg;
    	}
    }
}
