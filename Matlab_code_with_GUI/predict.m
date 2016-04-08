function predictions=predict(data,mapa,prototypes,w0,sig)
    gran_data=granulate_data(data,prototypes);
    t=size(data);
    t=t(1);
    c=size(prototypes);
    c=c(2);
    u_pre=zeros(t,c);
    for k=1:t-1
        for i=1:c
            tm=0;
            for j=1:c
                tm=tm+mapa(i,j)*gran_data(k,j);
            end
            tm=tm+w0(i);
            u_pre(k+1,i)=1/(1+exp((-1)*sig(i)*tm));
        end
    end
    predictions=degranulate(u_pre,prototypes);
end