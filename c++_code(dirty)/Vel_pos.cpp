#include "Vel_pos.h"

Vel_pos::Vel_pos(double val,int size)
{
     f=false;
    //_array=new double[size];
    _size=size;
    for(int i=0;i<size;i++)
        _array.push_back(val);
}
Vel_pos::Vel_pos(double * val,int size){
    f=false;
    //_array=new double[size];
    _size=size;
    for(int i=0; i<size; i++)
        _array.push_back(val[i]);
}
Vel_pos::Vel_pos(Vel_pos const& r){
    f=r.f;
    //_array=new double[r.get_size()];
    _size=r._size;
    //if(_size>0)
    _array=r._array;

}

Vel_pos::~Vel_pos()
{
	//if(f==false)
		//delete[] _array;
}


bool Vel_pos::operator>=(const Vel_pos& r){
    for(int i=0; i<_size; i++){
        //std::cout<<this->_array[0]<<"  "<<this->_array[1]<<">="<<r[i]<<std::endl;
        if(this->_array[i]<r[i])
            return false;
    }
    return true;
}
bool Vel_pos::operator<=(const Vel_pos& r){
    for(int i=0; i<_size; i++){
        std::cout<<this->_array[0]<<"  "<<this->_array[1]<<"<="<<r[i]<<std::endl;
        if(this->_array[i]>r[i])
            return false;
    }
    return true;
}
