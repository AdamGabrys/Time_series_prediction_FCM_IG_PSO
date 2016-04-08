function [fcm_m,fcm_v]=prepare_fcm_m(seCyNum,meCyNum,omega,c1,c2,c3, sub_swarm_size, part_num,u,t,c,pso_iter,v)
    global strach;
    strach=1;
    fcm_m_tab=zeros(c*(c+2));
    domaintab=zeros(2,c+2);
    for i=1:c
        domaintab(1,i)=-1;
       	domaintab(2,i)=1;
    end
    domaintab(1,c+1)=0;
    domaintab(2,c+1)=1;
    domaintab(1,c+2)=0;
    domaintab(2,c+2)=1000;
    domain=domaintab;
    pso=Pso(seCyNum,meCyNum,omega,c1,c2,c3,domain,sub_swarm_size,part_num,u,t,c);
    for j=1:pso_iter
        pso.do_next_it();
    end
    strach=strach+1;
    fcm_m_vec=zeros(c+2,c);
    fcm_m_vec(:,1)=pso.get_best_fit_arg();
    for i=2:c
        pso=Pso(seCyNum,meCyNum,omega,c1,c2,c3,domain,sub_swarm_size,part_num,u,t,c);
        for j=1:pso_iter
       		pso.do_next_it();
        end
	    strach=strach+1;
	    fcm_m_vec(:,i)=pso.get_best_fit_arg();
    end
    fcm_m_vec(c+3,:)=v;
    fcm_v= fcm_m_vec;
    fcm_m_vec=fcm_m_vec';
    for i=1:c
        for j=1:c
            fcm_m_tab(((i-1)*c)+j)=fcm_m_vec(i,j);
        end
	fcm_m_tab((c*c)+i)=fcm_m_vec(i,c+1);
	fcm_m_tab((c*c)+c+i)=fcm_m_vec(i,c+2);
    end
    fcm_m=fcm_m_tab;
end
       