classdef Sub_swarm < handle
   properties
       size;
       best_particle;
       particles;
   end
   methods
       
       function obj=Sub_swarm(part_per_sub_swarm,domain,u,t,c)
           obj.size=part_per_sub_swarm;
           obj.particles=Particle(domain,u,t,c);
           obj.best_particle=obj.particles;
           for i=2:part_per_sub_swarm
               obj.particles=[obj.particles Particle(domain,u,t,c)];
           end
       end
       
   end
end