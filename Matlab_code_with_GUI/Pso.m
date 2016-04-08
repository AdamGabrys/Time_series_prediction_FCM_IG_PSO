classdef Pso < handle
   
    properties
        swarm;
        it_num;
        se_cy_num;
        me_cy_num;
        omega;
        c1;
        c2;
        c3;
        u;
        mud_slow;
        t;
    end
    methods
        function obj=Pso(seCyNum,meCyNum,omega,c1,c2,c3,domain,sub_swarm_size,part_num,u,t,c)
            obj.it_num=0;
            obj.se_cy_num=seCyNum;
            obj.me_cy_num=meCyNum;
            obj.omega=omega;
            obj.c1=c1;
            obj.c2=c2;
            obj.c3=c3;
            obj.u=u;
            obj.t=t;
            obj.mud_slow=(1.0/1.2);
            obj.swarm=Swarm(domain,sub_swarm_size,part_num,u,t,c);
            obj.swarm.fit();
        end
        
        function v=get_best_fit(PSO)
           v=PSO.swarm.best_particle.best_fit;
        end
        
        function arg=get_best_fit_arg(PSO)
           arg=PSO.swarm.best_particle.best_arg;
        end

        function it=get_it_num(PSO)
           it=PSO.it_num; 
        end
        
        function PSO=do_next_it(PSO)
           for i=1:PSO.me_cy_num
              PSO.do_me(); 
           end
           for i=1:PSO.se_cy_num
               PSO.do_se();
           end
           PSO.it_num=PSO.it_num+1;
        end
        
        function do_se(PSO)
           for i=1:PSO.swarm.sub_swarm_size
               ss=PSO.swarm.sub_swarm(i);
               for j=1:PSO.swarm.sub_swarm(i).size
                   p=ss.particles(j);
                   while true
                       r1=rand;
                       r2=rand;
                       r3=rand;
                       v=PSO.omega*p.vel+PSO.c1*r1*(p.best_arg-p.arg)+PSO.c2*r2*(ss.best_particle.best_arg-p.arg)+PSO.c3*r3*(PSO.swarm.best_particle.best_arg-p.arg);
                       if(PSO.swarm.is_in_domain(p.arg+v))
                           p.fit(v);
                           break;
                       else
                           p.vel=p.vel*PSO.mud_slow;
                       end
                   end
               end
           end
           PSO.swarm.fit();
        end
       
       function do_me(PSO)
           for i=1:PSO.swarm.sub_swarm_size
               ss=PSO.swarm.sub_swarm(i);
               for j=1:ss.size
                   p=ss.particles(j);
                   while true
                       r1=rand;
                       r2=rand;
                       v=PSO.omega*p.vel+PSO.c1*r1*(p.best_arg-p.arg)+PSO.c2*r2*(ss.best_particle.best_arg-p.arg);
                       if(PSO.swarm.is_in_domain(p.arg+v))
                           p.fit(v);
                           break;
                       else
                           p.vel=p.vel*PSO.mud_slow;
                       end
                   end
               end
           end
           PSO.swarm.fit();
       end
    end
    
end