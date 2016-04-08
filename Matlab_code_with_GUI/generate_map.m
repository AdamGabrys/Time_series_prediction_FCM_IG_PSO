function [rmse_ret,fcm_v]=generate_map(data,c,se,me,sss,part_num,c1,c2,c3,omega,m,fcm_it_num,pso_it_num,map_name)
    t=size(data);
    t=t(1);
    t_l=round(t*0.8);
    t_t=t-t_l;
    data_l=data(1:t_l);
    data_t=data(t_l+1:t);
    fcm_options = [m fcm_it_num NaN 0];
    [v, u_l]=fcm(data_l,c,fcm_options);
    u_l=u_l';
    v=v';
    u_t=granulate_data(data_t,v);
    size(u_l)
    size(u_t)
    u= [u_l' u_t'];
    u=u';
    [fcm_t,fcm_v]=prepare_fcm_m(se,me,omega,c1,c2,c3,sss,part_num,u_l,t_l,c,pso_it_num,v);
    u_pre=u_pre_func(u,t,c,fcm_t);
    dat_pre=degranulate(u_pre,v);
    dat_pre_test=dat_pre(t_l+1:t);
    rmse_ret=rmse(dat_pre_test, data_t,t_t);
end