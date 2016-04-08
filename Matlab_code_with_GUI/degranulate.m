function data=degranulate(partition_matrix,prototypes)
    siz_pm=size(partition_matrix);
    m=2;
    t=siz_pm(1);
    c=siz_pm(2);
    data=zeros(t,1);
    for i=1:t
        sum=0;
        mian=0;
        for j=1:c
            sum=sum+(partition_matrix(i,j)^m)*prototypes(j);
            mian=mian+(partition_matrix(i,j)^m);
        end
        data(i)=sum/mian;
    end
end