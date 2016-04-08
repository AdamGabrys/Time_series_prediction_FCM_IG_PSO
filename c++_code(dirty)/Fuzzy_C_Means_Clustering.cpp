#include "Fuzzy_C_Means_Clustering.h"

Fuzzy_C_Means_Clustering::Fuzzy_C_Means_Clustering(std::vector<Vel_pos> dat, int c, int d,double m, int n):_d(d),_m(m)
{
    _it=0;
    _dat=dat;
    _n=n;
    _u.resize(_n);
    _c=c;
    _max_data_it=get_max_data_itter();
    _min_data_it=get_min_data_itter();
    for(int i=0; i<_n; i++){
        _u[i]=Vel_pos(0.0,_c);
        for(int j=0; j<_c; j++){
	    //if(j==0||j==_c-1)
		//_u[i][j]=0;
	   // if(i==_max_data_it||_min_data_it==i)
		//_u[i][j]=0;
            _u[i][j]=(double)rand()/(double)RAND_MAX;
        }
    }
    _v.resize(_c);
    for(int i=0; i<_c; i++){
        _v[i]=Vel_pos(0.0,_d);
    }
	/*_u[get_max_data_itter()][get_max_v_it()]=1;
	_u[get_min_data_itter()][get_min_v_it()]=1;
	_v[0]=Vel_pos(get_min_data(),_d);
	_v[_c-1]=Vel_pos(get_max_data(),_d);*/
}
void Fuzzy_C_Means_Clustering::show_part_matrix(){
	std::cout<<"  "<<std::endl;
	for(int i=0; i<_n; i++){
		std::cout<<i<<"  ";
	}
	std::cout<<std::endl;
	for(int i=0; i<_c; i++){
		std::cout<<"u"<<i;
		for(int j=0; j<_n; j++){
			std::cout<<_u[j][i]<<"  ";
		}
		std::cout<<std::endl;
	}
	
}
Fuzzy_C_Means_Clustering::~Fuzzy_C_Means_Clustering()
{

}
double Fuzzy_C_Means_Clustering::get_obj_func(std::vector<Vel_pos> u)const{
    double fit=0;
    for(int i=0;i<_n ;i++){
        for(int j=0; j<_c ;j++){
            fit+=pow(u[i][j],_m)*pow(distance(_dat,_v,i,j),2);
        }
    }
    return fit;
    /*double obfun=std::abs(_uo[0][0]-_u[0][0]);
    double tmp;
    for(int i=0; i<_n; i++){
	for(int j; j<_c; j++){
		tmp=std::abs(_uo[i][j]-_u[i][j]);
		if(tmp<obfun)
			obfun=tmp;
	}
    }
    return obfun;*/
}

void Fuzzy_C_Means_Clustering::upd_pro_mat(){
    for(int i=0; i<_c; i++){
        for(int j=0; j<_d; j++){
            double tmp1=0;
            double tmp2=0;
            for(int k=0; k<_n; k++){
                tmp1+=pow(_u[k][i],_m)*_dat[k][j]; //przeciazenie operatora Vel_pos*double
                tmp2+=pow(_u[k][i],_m);
            }
            	_v[i][j]=tmp1/tmp2;
        }
    }
}

void Fuzzy_C_Means_Clustering::upd_par_mat(){
    for(int i=0; i<_c; i++){
        for(int j=0; j<_n; j++){
            double tmp1=0;
            double dst=distance(_dat,_v,j,i);
            for(int k=0; k<_c; k++){
                tmp1+=pow((dst/distance(_dat,_v,j,k)),(2.0/(_m-1)));
            }
            _u[j][i]=1.0/tmp1;
        }
    }
    /*_uo=_u;
    for(int k=0; k<_n; k++){
	for(int i=0; i<_c; i++){
		double l=0;
		double m=0;
		double dif=0;
		for(int j=0; j<_c; j++){
			l=std::abs(_dat[k][0]-_v[0][i]);
			m=std::abs(_dat[k][0]-_v[0][j]);
			dif+=pow((l/m),(2./(_m-1)));
		}
		_u[k][i]=1./dif;
	}
     }*/
}

void Fuzzy_C_Means_Clustering::correct_v(){
    //int max_it_v=get_max_v_it();
    int min_it_v=get_min_v_it();
   // double max_dat=get_max_data();
    double min_dat=get_min_data();
    //_v[max_it_v][0]=max_dat;
    _v[min_it_v][0]=min_dat;
    //std::cout<<"max it: "<<max_it_v<<" max dat: "<<max_dat<<std::endl<<std::endl;
    //std::cout<<"min it: "<<min_it_v<<" min dat: "<<min_dat<<std::endl<<std::endl;
}

double Fuzzy_C_Means_Clustering::get_max_data(){
    double max_dat=_dat[0][0];
    for(int i=0; i<_n; i++){
	if(max_dat<_dat[i][0])
		max_dat=_dat[i][0];
    } 
    return max_dat;
}
double Fuzzy_C_Means_Clustering::get_min_data(){
    double min_dat=_dat[0][0];
    for(int i=0; i<_n; i++){
	if(min_dat>_dat[i][0])
		min_dat=_dat[i][0];
    }
    return min_dat;
}

int Fuzzy_C_Means_Clustering::get_max_data_itter(){
    int max_dat_it=0;
    for(int i=0; i<_n; i++){
	if(_dat[max_dat_it][0]<_dat[i][0])
		max_dat_it=i;
    } 
    return max_dat_it;
}

int Fuzzy_C_Means_Clustering::get_min_data_itter(){
    int min_dat_it=0;
    for(int i=0; i<_n; i++){
	if(_dat[min_dat_it][0]>_dat[i][0])
		min_dat_it=i;
    } 
    return min_dat_it;
}


int Fuzzy_C_Means_Clustering::get_max_v_it(){
    int max_it_v=0;
    for(int i=0; i<_c; i++){
	if(_v[max_it_v][0]<_v[i][0])
		max_it_v=i;
    }
    return max_it_v;
}

int Fuzzy_C_Means_Clustering::get_min_v_it(){
    int min_it_v=0;
    for(int i=0; i<_c; i++){
	if(_v[min_it_v][0]>_v[i][0])
		min_it_v=i;
    }
    return min_it_v;
}


void Fuzzy_C_Means_Clustering::do_next_it(){
    upd_pro_mat();
    upd_par_mat();
    //correct_v();
}

double Fuzzy_C_Means_Clustering::distance(std::vector<Vel_pos> dat, std::vector<Vel_pos> v, int a, int b)const{
    double ret=0;
    for(int i=0; i<_d; i++){
        ret+=pow((dat[a][i]-v[b][i]),2);
    }
    ret=std::sqrt(ret);
    return ret;
}
