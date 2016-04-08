#ifndef prepare_fcm_m_h
#define prepare_fcm_m_h
#include "Vel_pos.h"
#include <cmath>
#include <vector>
#include "nsstr.h"
#include <iostream>
#include "Pso.h"
#include <cstring>
#include <fstream>

inline Vel_pos prepare_fcm_m(int seCyNum,int meCyNum, double omega,double c1,double c2,double c3,int sub_swarm_size, int part_num,std::vector<Vel_pos> u, int t, int c,bool f, int pso_iter){
    nsstr::strach=0;
	std::ofstream file_w;
	char* file_name="mapa";
	strcat(file_name,(char)c)
	file_w.open(file_name,std::ios_base::app);
    Vel_pos arg;
    std::vector< double* > domaintab;
    std::vector<Vel_pos > fcm_m_vec;
    Vel_pos fcm_m;
    double * fcm_m_tab;
    fcm_m_tab=new double[c*(c+2)];
    domaintab.resize(2);
    for(int i=0; i<2;i++)
	domaintab[i]=new double[c+2];
    for(int i=0; i<c;i++){
        domaintab[0][i]=-1;
       	domaintab[1][i]=1;
    }
    domaintab[0][c]=0;
    domaintab[1][c]=1;
    domaintab[0][c+1]=0;
    domaintab[1][c+1]=1000;
    std::vector<Vel_pos> domain;
    domain.push_back(Vel_pos(domaintab[0],c+2));
    domain.push_back(Vel_pos(domaintab[1],c+2));
    for(int i=0; i<c+2; i++){
	std::cout<<"range: "<<domain[0][i]<<"  to  "<<domain[1][i]<<std::endl;
    }
    for(int i=0; i<c; i++){
	Pso pso(seCyNum,meCyNum,omega,c1,c2,c3,domain,sub_swarm_size,part_num,u,t,c,f);
    	for(int j=0; j<pso_iter; j++){
       		pso.do_next_it();
		std::cout<<" dla c: "<<i<<"  iteracja: "<<pso.get_it_num()<<"  najlepsze dopasowanie: "<<pso.get_best_fit()<<std::endl;
		for(int k=0; k<c+2; k++){
			std::cout<<pso.get_best_fit_arg()[k]<<std::endl;
		}
	}
	nsstr::strach++;
	arg=pso.get_best_fit_arg();
	fcm_m_vec.push_back(arg);
    }
    for(int i=0; i<c;i++){
	for(int j=0; j<c; j++){
		fcm_m_tab[(i*c)+j]=fcm_m_vec[i][j];
	}
	fcm_m_tab[(c*c)+i]=fcm_m_vec[i][c];
	fcm_m_tab[(c*c)+c+i]=fcm_m_vec[i][c+1];
    }
    fcm_m=Vel_pos(fcm_m_tab,c*(c+2));
    delete [] fcm_m_tab;
    for(int i=0; i<c+2; i++){
		for(int j=0; j<c; j++){
			file_w<<fcm_m[i*j+j]<<",";
		}
		file_w<<std::endl;
    }
	file_w.close();
    return fcm_m;
}

#endif //prepare_fcm_m_h
