#ifndef RMSE_H_INCLUDED
#define RMSE_H_INCLUDED
#include <cmath>
#include <vector>
inline double rmse(double* dat, std::vector<double> dat_or ,int t){
	//double dat_s=0;
	double dif=0;
	double ret;
	/*for(int i=0; i<t; i++){
		dat_s+=dat[i];
	}
	dat_s=dat_s/(double)t;*/
	for(int i=0; i<t; i++){
		dif+=pow(dat[i]-dat_or[i],2);
	}
	ret=sqrt(dif/(double)t);
	return ret;
}
#endif // RMSE_H_INCLUDED
