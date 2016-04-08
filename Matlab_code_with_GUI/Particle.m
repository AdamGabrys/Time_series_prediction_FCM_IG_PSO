classdef Particle < handle
    properties
        vel;
        arg;
        best_fit;
        best_arg;
        cur_fit;
        domain;
        u;
        t;
        c;
    end
    methods
        
        function obj=Particle(domain,u,t,c)
            obj.t=t;
            obj.c=c;
            obj.u=u;
            ds=size(domain);
            ds=ds(2);
            obj.arg=(rand*(domain(2,1)-domain(1,1))+domain(1,1));
            obj.vel=0;
            for i=2:ds
                obj.arg=[obj.arg (rand*(domain(2,i)-domain(1,i))+domain(1,i))];
                obj.vel=[obj.vel 0];
            end
            obj.cur_fit=fit_func(u,t,c,obj.arg);
            obj.best_fit=obj.cur_fit;
            obj.best_arg=obj.arg;
            
        end
     
        
        function Particle=fit(Particle,v)
            Particle.vel=v;
            Particle.arg=Particle.arg+v;
            Particle.cur_fit=fit_func(Particle.u,Particle.t,Particle.c,Particle.arg);
            if(Particle.cur_fit<=Particle.best_fit)
                Particle.best_fit=Particle.cur_fit;
                Particle.best_arg=Particle.arg;
            end
        end
    end
        
end