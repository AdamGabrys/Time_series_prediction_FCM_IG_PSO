classdef Swarm < handle
    properties
        best_particle;
        sub_swarm_size;
        sub_swarm;
        domain;
    end
    methods
        
        function obj=Swarm(domain,sub_swarm_size,part_num,u,t,c)
           obj.domain=domain;
           obj.sub_swarm_size=sub_swarm_size;
           part_per_sub_swarm=round(part_num/sub_swarm_size);
           obj.sub_swarm=Sub_swarm(part_per_sub_swarm,domain,u,t,c);
           for i=2:sub_swarm_size
               obj.sub_swarm=[obj.sub_swarm Sub_swarm(part_per_sub_swarm,domain,u,t,c)];
           end
           obj.best_particle=obj.sub_swarm(1).best_particle;
           obj.fit();
        end
        
        function fit(Swarm)        
           for i=1:Swarm.sub_swarm_size
                ss=Swarm.sub_swarm(i);
                for j=1:ss.size
                    p=ss.particles(j);
                    if(p.best_fit<Swarm.best_particle.best_fit)
                        Swarm.best_particle=p;
                    end
                    if(p.best_fit<ss.best_particle.best_fit)
                        ss.best_particle=p;
                    end
                end
            end 
        end
        
        function logic=is_in_domain(Swarm,val)
            logic=true;
            siz=size(val);
            siz=siz(2);
            for i=1:siz
                if(Swarm.domain(1,i)>=val(i)||Swarm.domain(2,i)<=val(i))
                    logic=false;
                end
            end
        end
       
        
    end
end