#include "Pso.h"
#include "Vel_pos.h"
#include "Fuzzy_C_Means_Clustering.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "u_pre_func_a.h"
#include "u_to_dat.h"
#include "rmse.h"
#include "prepare_fcm_m.h"
#include "cor_part_mat.h"
#include "nsstr.h"
#include "gran_int.h"
#include <time.h>
#include <cstring>
namespace nsstr{
	int strach=0;
}
int main(int argc, char** argv){
double tstart, tstop, ttime;
tstart = (double)clock()/CLOCKS_PER_SEC;
    srand(time(0));
    std::string csv_value;
    const char* csv;
    char* end;
    std::ifstream file_r;
    file_r.open(argv[1]);
    std::vector<double> csv_values;
    while(file_r.good()){
	std::getline(file_r,csv_value,',');
	std::cout<<csv_value<<std::endl;	
	csv=csv_value.c_str();
	csv_values.push_back(std::strtod(csv,&end));
    }
    std::vector<Vel_pos> dat_l;
    std::vector<Vel_pos> dat_t;
    int t=csv_values.size();
    int t_l=0.8*t;
    int t_t=t-t_l;
    int sep=0; 
    std::cout<<t_l<<"  "<<t_t<<std::endl;
    for(std::vector<double>::iterator it=csv_values.begin(); it!=csv_values.end(); it++){
	if(sep<t_l)	
		dat_l.push_back(Vel_pos(*it,1));
	else
		dat_t.push_back(Vel_pos(*it,1));
	sep++;
    }
    int se=std::atoi(argv[3]);
    int me=std::atoi(argv[4]);
    int sss=std::atoi(argv[5]);
    int part_num=std::atoi(argv[6]);
    int c=std::atoi(argv[7]);
    int pso_iter=std::atoi(argv[8]);
    double c1=std::atof(argv[9]);
    double c2=std::atof(argv[10]);
    double c3=std::atof(argv[11]);
    double omega=std::atof(argv[12]);
    double m=std::atof(argv[13]);
    Fuzzy_C_Means_Clustering f1(dat_l,c,1,m,t_l);
    for(int i=0;i<15;i++){
        f1.do_next_it();
        std::cout<<"obj_func_fcm: "<<f1.get_obj_func(f1.get_u())<<std::endl;
    }
    std::vector<Vel_pos> u_l=f1.get_u();
    std::vector<Vel_pos> u_t=gran_int_h(f1.get_v(),t_t ,c,dat_t);
    std::vector<Vel_pos> u=u_l;
    u.insert(u.end(),u_t.begin(),u_t.end());
    std::vector<Vel_pos> u_pre;
    u_pre=u_pre_func(u,t,c,prepare_fcm_m(se,me,omega,c1,c2,c3,sss,part_num,u_l,t_l,c,false,pso_iter));
    double* dat_f;std::cout<<"b";
    dat_f=u_to_dat(u_pre,f1.get_v(),t,c,m);
    dat_f[0]=csv_values[0];
    double mse=rmse(dat_f, csv_values,t);
	tstop = (double)clock()/CLOCKS_PER_SEC;
    delete [] dat_f;
    file_r.close();
    delete [] csv;
    delete [] end;
    return 0;
}