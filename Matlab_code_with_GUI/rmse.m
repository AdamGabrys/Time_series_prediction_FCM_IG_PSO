function ret=rmse(dat,dat_or,t)
	dif=0;
    for i=1:t
		dif=dif+(dat(i)-dat_or(i))^2;
    end
	ret=sqrt(dif/t);
end