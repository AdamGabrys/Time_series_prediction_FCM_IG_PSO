#ifndef FIT_FUNC_FCM_H_INCLUDED
#define FIT_FUNC_FCM_H_INCLUDED
#include "Vel_pos.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include "u_to_dat.h"
#include "nsstr.h"
#include "normalize_arg.h"

inline double fit_func_fcm(std::vector<Vel_pos> u, int t,int c, Vel_pos arg){
    std::string csv_value;
    std::vector<Vel_pos> u_n;
    u_n.resize(t);
    for(int i=0; i<t; i++){
	u_n[i]=u[i];
    }
    double* dat_pre;
    const char* csv;
    char* end;
    std::ifstream file_r;
    file_r.open("enrolment");
    std::vector<double> csv_values;
    while(file_r.good()){
	std::getline(file_r,csv_value,',');	
	csv=csv_value.c_str();
	csv_values.push_back(std::strtod(csv,&end));
    }
    std::vector<Vel_pos> dat;
    //int t=csv_values.size();
    for(std::vector<double>::iterator it=csv_values.begin(); it!=csv_values.end(); it++){
	dat.push_back(Vel_pos(*it,1));
    }
    std::vector<Vel_pos> v;
    v.resize(c);
    for(int i=0; i<c; i++){
        for(int j=0; j<1; j++){
            double tmp1=0;
            double tmp2=0;
            for(int k=0; k<t; k++){
                tmp1+=pow(u[k][i],2)*dat[k][j]; //przeciazenie operatora Vel_pos*double
                tmp2+=pow(u[k][i],2);
            }
            	v[i][j]=tmp1/tmp2;
        }
    }
   /* double sum_to_1=0;
    for(int i=0; i<c; i++){
	sum_to_1+=arg[i];
    }
   // if(nsstr::strach==0){
	for(int i=0; i<c; i++){u_n[nsstr::strach][i]=arg[i];
    		//std::cout<<"arg for i=0 : "<<arg[i]<<std::endl;
    }*/
    
    u_n[nsstr::strach]=normalize_arg(arg,c);
    dat_pre=u_to_dat(u_n,v,t,c,2);
    double ret=std::pow(csv_values[nsstr::strach]-dat_pre[nsstr::strach],2);
    delete [] dat_pre;
    delete [] csv;
    delete [] end;
    //std::cout<<nsstr::strach<<std::endl;
    //std::cout<<dat_pre[nsstr::strach]<<std::endl;
    //std::cout<<std::pow(csv_values[nsstr::strach]-dat_pre[nsstr::strach],2)<<std::endl;
    return ret;
}
#endif 
