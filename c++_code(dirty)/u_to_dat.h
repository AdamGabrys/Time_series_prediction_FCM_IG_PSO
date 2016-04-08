#ifndef U_TO_DAT_H_INCLUDED
#define U_TO_DAT_H_INCLUDED
#include<vector>
#include<cmath>
inline double* u_to_dat(std::vector<Vel_pos> u, std::vector<Vel_pos> v,int t, int c, int m){
    double * dat=new double[t];
    for(int i=0; i<t; i++){
        double sum=0;
	double mian=0;
        for(int j=0;j<c;j++){
            sum+=pow(u[i][j],m)*v[j][0];
	    mian+=pow(u[i][j],m);
        }
        dat[i]=sum/mian;
    }
    return dat;
}

#endif // U_TO_DAT_H_INCLUDED
