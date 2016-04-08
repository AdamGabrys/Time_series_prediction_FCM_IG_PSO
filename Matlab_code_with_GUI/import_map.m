function [mapa_ret,v_ret,w0_ret,sig_ret]=import_map(mapa_arg)
    mapa=csvread(mapa_arg);
    siz=size(mapa);
    row=siz(1);
    v_ret=mapa(row,:);
    sig_ret=mapa(row-1,:);
    w0_ret=mapa(row-2,:);
    mapa_ret=mapa(1:row-3,:);