function dist=distance(x, v, k ,i)
dist=sqrt(sum((x(k,:)-v(i,:)).^2));
end