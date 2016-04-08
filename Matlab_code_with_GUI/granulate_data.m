function gran_data=granulate_data(data,prototypes)
    siz_pro=size(prototypes);
    c=siz_pro(2);
    siz_dat=size(data);
    n=siz_dat(1);
    u=zeros(n,c); 
    tmps1=0;
    m=2;
    prototypes=prototypes';
    for t=1:c
        for s=1:n
            dst=distance(data,prototypes,s,t);
            for j=1:c
                    tmps1=tmps1+(dst/distance(data,prototypes,s,j))^(1/(m-1));
            end
            u(s,t)=1/tmps1;
            tmps1=0;
        end
    end
    gran_data=u;
end