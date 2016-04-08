#ifndef U_PRE_FUNC_A_H_INCLUDED
#define U_PRE_FUNC_A_H_INCLUDED

inline std::vector<Vel_pos> u_pre_func(std::vector<Vel_pos> u, int t,int c, Vel_pos arg){
        std::vector<Vel_pos> fuzy_con_map;
        fuzy_con_map.resize(c);
        for(int i=0; i< c; i++){
            fuzy_con_map[i]=Vel_pos(0.0,c);
        }
        for(int i=0; i<c; i++){
            for(int j=0;j<c;j++){
                fuzy_con_map[i][j]=arg[(i*c)+j];
		std::cout<<"fcm map: "<<fuzy_con_map[i][j]<<"  ";
            }
	    std::cout<<std::endl;
        }
        Vel_pos w0(0.0,c);
        Vel_pos sig(0.0,c);
        for(int i=0; i< c; i++){
            w0[i]=arg[(c*c)+i];
            sig[i]=arg[((c*(c+1)+i))];
	    std::cout<<"w0: "<<w0[i]<<"  sig "<<sig[i]<<std::endl;
        }
        Vel_pos tmp1(1.0,c);
        std::vector<Vel_pos> u_pre;
	u_pre.resize(t);
        for(int i=0; i<t; i++){
            u_pre[i]=Vel_pos(1.0,c);
        }
	/*for(int i=0; i<c; i++){
	    u_pre[0][i]=u[0][i];
	    u_pre[1][i]=u[1][i]; //dodanbe
	//std::cout<<" u_pre asdsadasd "<<u_pre[0][i]<<std::endl;
	}*/
	//u_pre[0]=u[0];
	u_pre[0]=Vel_pos(0.0,c);
	for(int i=0; i<c; i++){
		u_pre[0][i]=u[0][i];
		std::cout<<" u pre 0: "<<u_pre[0][i]<<std::endl;
	}
	Vel_pos u_last;
	//u_last=Vel_pos(0.0,c);
        for(int k=0; k<t-1; k++){ //tu i tam dodane
            for(int i=0; i<c; i++){
	    double tm=0;
                for(int j=0; j<c; j++){
			tm+=fuzy_con_map[i][j]*u[k][j];
                }  
                tm+=w0[i];
                u_pre[k+1][i]=1.0/(1.0+std::exp(-1.0*sig[i]*tm));
		//std::cout<<"u_pre k+1: "<<k+1<<"  i: "<<i<<"  "<<u_pre[k+1][i]<<std::endl;
            }
        }
	/*for(int i=0; i<t; i++){
		for(int j=0; j<c; j++){
			std::cout<<"i: "<<i<<"  j: "<<j<<
		}
	}*/
        return u_pre;
}

#endif // U_PRE_FUNC_A_H_INCLUDED
