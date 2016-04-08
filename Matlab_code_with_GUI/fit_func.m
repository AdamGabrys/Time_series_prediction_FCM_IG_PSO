function ret=fit_func(u,t,c,arg)
        global strach;
        fuzy_con_map=zeros(1,c);
        for j=1:c
            fuzy_con_map(1,j)=arg(j);
        end
        w0=arg(c+1);
        sig=arg(c+2);
    	u_pre=zeros(t,1);
        u_pre(1)=u(1,strach);
        for k=1:t-1
            tm=0;
                for j=1:c
                    tm=tm+fuzy_con_map(1,j)*u(k,j);
                end
                tm=tm+w0;
                u_pre(k+1)=1.0/(1.0+exp(-1.0*(sig*tm)));
        end
        ret=0;
        for k=1:t-1
            tm1=0;
            tm1=tm1+(u_pre(k+1)-u(k+1,strach))^2;
            ret=ret+sqrt(tm1);
        end
        ret=(ret*1.0)/(t-1);
end
