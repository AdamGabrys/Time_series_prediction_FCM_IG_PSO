#ifndef NORMALIZE_ARG_H
#define NORMALIZE_ARG_H

#include "Vel_pos.h"
#include <vector>

inline Vel_pos normalize_arg(Vel_pos arg,int c){
	Vel_pos ret(0.0,c);
	double sum=0;
	for(int i=0; i<c; i++){
		sum+=arg[i];
	}
	for(int i=0; i<c; i++){
		ret[i]=arg[i]/sum;
	}
	return ret;
}

#endif //NORMALIZE_ARG_H
