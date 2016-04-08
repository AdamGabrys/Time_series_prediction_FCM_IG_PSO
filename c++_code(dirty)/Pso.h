#ifndef PSO_H
#define PSO_H
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "Swarm.h"
#include "Vel_pos.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>
//#include <graphics.h>
//#include "stdlib.h"

class Pso
{
    public:
        Pso(int seCyNum,int meCyNum, double omega,double c1,double c2,double c3,std::vector<Vel_pos> domain,int sub_swarm_size, int part_num,std::vector<Vel_pos> u, int t, int c,bool f);
	Pso(Pso const& cpy){
		_f=cpy._f;
		_swarm=cpy.get_swarm();
		_it_num=cpy._it_num;
		_se_cy_num=cpy._se_cy_num;
		_me_cy_num=cpy._me_cy_num;
		mud_slow=cpy.mud_slow;
		_t=cpy._t;
		//_u=new Vel_pos[_t];
		_u=cpy._u;
		
	}
	Pso& operator=(Pso rsh){
		rsh.swap(*this);
		return *this;
	}
	void swap(Pso& s){
		std::swap(this->_f,s._f);
		std::swap(this->_swarm,s._swarm);
		std::swap(this->_it_num,s._it_num);
		std::swap(this->_se_cy_num,s._se_cy_num);
		std::swap(this->_me_cy_num,s._me_cy_num);
		std::swap(this->mud_slow,s.mud_slow);
		std::swap(this->_t,s._t);
		std::swap(this->_u,s._u);
	}
        virtual ~Pso();
        double get_best_fit();
	Swarm get_swarm()const{return _swarm;}
        Vel_pos get_best_fit_arg();
        int get_it_num();
	void set_omega(double omega){_omega=omega;}
        void do_next_it();
    protected:
    private:
        Swarm _swarm;
        int _it_num;
        int _se_cy_num, _me_cy_num;
        double _omega, _c1, _c2, _c3;
        std::vector<Vel_pos> _u; //macierz podzialow
        double mud_slow;
        void _do_se();
        void _do_me();
	int _t;
	bool _f;
};

#endif // PSO_H
