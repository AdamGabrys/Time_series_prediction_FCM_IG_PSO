function u_pre=u_pre_func(u,t,c, arg)
        fuzy_con_map=zeros(c);
        for i=1:c
            for j=1:c
                fuzy_con_map(i,j)=arg(((i-1)*c)+j);
            end
        end
        w0=zeros(c,1);
        sig=zeros(c,1);
        for i=1:c
            w0(i)=arg((c*c)+i);
            sig(i)=arg(((c*(c+1)+i)));
        end
        u_pre=zeros(t,c);
        for i=1:c
            u_pre(1,i)=u(1,i);
        end
        for k=1:t-1
            for i=1:c
                tm=0;
                for j=1:c
                    tm=tm+fuzy_con_map(i,j)*u(k,j);
                end
                tm=tm+w0(i);
                u_pre(k+1,i)=1.0/(1.0+exp(-1.0*sig(i)*tm));
            end
        end
end