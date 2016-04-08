#ifndef DISTANCE_H_INCLUDED
#define DISTANCE_H_INCLUDED
#include "Vel_pos.h"
#include <cmath>
#include <vector>
#include <iostream>
inline double distance(std::vector<Vel_pos> dat, std::vector<Vel_pos> v, int a, int b){
    double ret=0;
    for(int i=0; i<1; i++){
        ret+=pow((dat[a][i]-v[b][i]),2);
    }
    ret=std::sqrt(ret);
    return ret;
}

#endif //DISTANCE_H_
