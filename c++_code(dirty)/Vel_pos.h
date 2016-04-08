#ifndef VEL_POS_H
#define VEL_POS_H
#include <iostream>
#include <vector>
#include <algorithm>
class Vel_pos
{
    public:
        Vel_pos(){f=true;_size=2;_array.resize(_size);}
        Vel_pos(double val, int size);
        Vel_pos(double* val, int size);
        Vel_pos(const Vel_pos& r);
        double& operator[](const int itt){return _array[itt];}
        const double& operator[](const int itt)const{return _array[itt];}
        bool operator<=(const Vel_pos& r);
        bool operator>=(const Vel_pos& r);
        int get_size()const {return _size;}
	std::vector<double> get_array()const {return _array;}
	int& get_point_size(){return _size;}
	std::vector<double>& get_point_array(){return _array;}
	Vel_pos& operator=(Vel_pos rhs){rhs.swap(*this); return *this;}
	void swap(Vel_pos &s)
         {
	     std::swap(f,s.f);
	     //bool tmpf=f;
	     //f=s.f;
	     //s.f=tmpf;
             _array.swap(s._array);
	     //int tmps=_size;
	     //_size=s._size;
	     //s._size=tmps;
             std::swap(_size ,s._size);
         }

        virtual ~Vel_pos();
    	protected:
    	private:
        std::vector<double> _array;
        int _size;
	bool f;

};

inline Vel_pos operator*(const double& l,const Vel_pos& r){
    double* tab;
    int size=r.get_size();
    tab=new double[size];
    for(int i=0;i<size;i++){
        tab[i]=l*r[i];}
    Vel_pos ret=Vel_pos(tab,r.get_size());
    //std::cout<<"ziaziu"<<std::endl;
    delete [] tab;

    return ret;
}
inline Vel_pos operator+(const Vel_pos& l, const Vel_pos& r){
    double *tab;
    tab=new double[r.get_size()];
    for(int i=0; i<r.get_size();i++)
        tab[i]=l[i]+r[i];
    Vel_pos ret=Vel_pos(tab,r.get_size());
    delete [] tab;
    return ret;
}

inline Vel_pos operator-(const Vel_pos& l, const Vel_pos& r){
    double *tab;
    tab=new double[r.get_size()];
    for(int i=0; i<r.get_size();i++)
        tab[i]=l[i]-r[i];
    Vel_pos ret(tab,r.get_size());
    //std::cout<<l[1]<<"-"<<r[1]<<"="<<ret[1]<<std::endl;
    delete [] tab;
    return ret;
}

#endif // VEL_POS_H
