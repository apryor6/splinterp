N = 1024;
n = 1000;
vec   = repmat(10:999,[1, 10]);
vec = 1:1024;
vec_c = vec - 1;
% b = rand(N,N) + 1j*rand(N,N);
b = rand(N,N);

[xx,yy] = meshgrid(1:N,1:N);

tic

for i = 1:n
    c1 = interp2(b,vec,vec);
end
t1 = toc


tic
for i = 1:n
    c2 = splinterp2(b,vec_c,vec_c);
end
t2 = toc
t1./t2
sum(abs(c1(:)-c2(:)))

