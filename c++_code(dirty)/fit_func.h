#ifndef FIT_FUNC_H_INCLUDED
#define FIT_FUNC_H_INCLUDED
#include "Vel_pos.h"
#include <cmath>
#include <vector>
#include <iostream>
#include "nsstr.h"
inline double fit_func(std::vector<Vel_pos> u, int t,int c, Vel_pos arg){
        std::vector<Vel_pos> fuzy_con_map;
        fuzy_con_map.resize(c);
        for(int i=0; i<1; i++){
            fuzy_con_map[i]=Vel_pos(1.0,c);
        }
        for(int i=0; i<1; i++){
            for(int j=0;j<c;j++){
                fuzy_con_map[i][j]=arg[(i*c)+j];
            }
        }
        Vel_pos w0(1.0,1);
        Vel_pos sig(1.0,1);
        for(int i=0; i<1; i++){
            w0[i]=arg[c+i];
            sig[i]=arg[c+1+i];
        }
        Vel_pos tmp1(1.0,c);
        std::vector<Vel_pos> u_pre;
	u_pre.resize(t);
        for(int i=0; i<t; i++){
            u_pre[i]=Vel_pos(1.0,1);
        }
	/*for(int i=0; i<c; i++){
	    u_pre[0][i]=u[0][i];
	    //u_pre[1][i]=u[0][i];//dodane
		//std::cout<<"bafasdsad: "<<u_pre[0][i]<<std::endl;
	}*/
	u_pre[0][0]=u[0][nsstr::strach];
        for(int k=0; k<t-1; k++){
	    double tm=0;
                for(int j=0; j<c; j++){
                    tm+=fuzy_con_map[0][j]*u[k][j];
                }
                tm+=w0[0];
                u_pre[k+1][0]=1.0/(1.0+std::exp(-1.0*(sig[0]*tm)));
        }
        double ret=0;
        for(int k=0;k<t-1;k++){
            double tm1=0;
                tm1+=pow(u_pre[k+1][0]-u[k+1][nsstr::strach],2); //uwaga ui
            ret+=std::sqrt(tm1);
        }
        ret=ret*1.0/(double)(t-1);
        return ret;
}
#endif // FIT_FUNC_H_INCLUDED
