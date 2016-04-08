#ifndef GRAN_INT_H_INCLUDED
#define GRAN_INT_H_INCLUDED
#include "Vel_pos.h"
#include <cmath>
#include <vector>
#include <iostream>
#include "distance.h"
inline std::vector<Vel_pos> gran_int_h(std::vector<Vel_pos> v, int t,int c, std::vector<Vel_pos> dat_t){
    std::vector<Vel_pos> u;
    u.resize(t);
    for(int i=0; i<t; i++)
	u[i]=Vel_pos(0.0,c);
    for(int i=0; i<c; i++){
        for(int j=0; j<t; j++){
            double tmp1=0;
            double dst=distance(dat_t,v,j,i);
            for(int k=0; k<c; k++){
                tmp1+=pow((dst/distance(dat_t,v,j,k)),2);
            }
            u[j][i]=1.0/tmp1;
        }
    }
    return u;
}

#endif //GRAN_INT_H_
