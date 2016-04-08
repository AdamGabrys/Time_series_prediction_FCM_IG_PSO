#ifndef FUZZY_C_MEANS_CLUSTERING_H
#define FUZZY_C_MEANS_CLUSTERING_H
#include "Vel_pos.h"
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <vector>

class Fuzzy_C_Means_Clustering
{
    public:
        Fuzzy_C_Means_Clustering(std::vector<Vel_pos> dat, int c, int d,double m,int n);
        virtual ~Fuzzy_C_Means_Clustering();
        void do_next_it();
        std::vector<Vel_pos> get_v()const{return _v;}
        std::vector<Vel_pos> get_u()const{return _u;}
        double get_obj_func(std::vector<Vel_pos> u)const;
	int get_min_v_it();
	int get_max_v_it();
	double get_max_data();
	double get_min_data();
	int get_min_data_itter();
	int get_max_data_itter();
	void correct_v();
	void show_part_matrix();
    protected:
        void upd_par_mat();
        void upd_pro_mat();
	int _it;
	int _max_data_it;
	int _min_data_it;
        int _n; //value of data elements number
        int _d; //dimension of data elements
        double _m; //real number ...
        int _c;
        double distance(std::vector<Vel_pos> dat, std::vector<Vel_pos> v, int a, int b)const;
        std::vector<Vel_pos> _u;
	std::vector<Vel_pos> _uo;
        std::vector<Vel_pos> _v;
        std::vector<Vel_pos> _dat;
    private:
};

#endif // FUZZY_C_MEANS_CLUSTERING_H
