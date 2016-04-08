#ifndef COR_PART_MAT_H_INCLUDED
#define COR_PART_MAT_H_INCLUDED
#include "Vel_pos.h"
#include "Pso.h"
#include "nsstr.h"
#include <cmath>
#include <vector>
#include <iostream>
#include "normalize_arg.h"
inline std::vector<Vel_pos> cor_part_mat(std::vector<Vel_pos> u, int t,int c){
    //nsstr::zero_str();
    //nsstr::strach=0;
    std::vector<Vel_pos> u_cor;
    u_cor.resize(t);
    std::vector<std::vector<double> > domaintab;
    domaintab.resize(c);
    for(int i=0; i<c;i++)
	domaintab[i].resize(2);
    int se=5,me=2, c1=1,c2=1,c3=2,sss=2,part_num=100;
    double omega=0.75;
    for(int i=0; i<1;i++){
	for(int j=0; j<c; j++){
        	domaintab[(i+1)*(j+1)-1][0]=0;
        	domaintab[(i+1)*(j+1)-1][1]=1;
	}
    }
    std::vector<Vel_pos> domain;
    domain.push_back(Vel_pos(domaintab[0][0],c));
    domain.push_back(Vel_pos(domaintab[0][1],c));
std::cout<<"jestek tu"<<std::endl;
    for(int i=0; i<t; i++){
    	Pso pso(se,me,omega,c1,c2,c3,domain,sss,part_num,u,t,c,true);
	for(int j=0; j<20; j++){
		pso.do_next_it();
		std::cout<<pso.get_best_fit()<<std::endl;
	}
	u_cor[nsstr::strach]=normalize_arg(pso.get_best_fit_arg(),c);
       // for(int i=0; i<)
	//nsstr::incr_str();;
		std::cout<<"next best fit  "<<std::endl;
	nsstr::strach++;
    }
    //double fit=0;
    /*for(int i=0;i<t ;i++){
        for(int j=0; j<c ;j++){
            fit+=pow(u_cor[i][j],2)*pow(distance(dat,_v,i,j),2);
        }
    }*/
    /*for(int i=0; i<t; i++){
	for(int j=0; j<c; j++)
		std::cout<<i<<"  "<<j<<"  "<<u_cor[i][j]<<std::endl;
    }*/
    return u_cor;
	
}
#endif //COR_PART_MAT_H
