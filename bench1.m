clear    
N = 4096^2;
n = 1;
vec = 1:100000;
vec_c = vec;
b = rand(N,1) + 1j*rand(N,1);
xx = 1:N;
tic
c1 = interp1(b,vec);
t1 = toc

tic
c2 = splinterp1(b,vec_c);
t2 = toc;
speedup = t1./t2
sum(abs(c1(:)-c2(:)))
    

