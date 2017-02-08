

clear
addpath ../
its = 50;
Ns = 5:25:8192;
t_matlab = zeros(1,numel(Ns));
t_cpp = zeros(1,numel(Ns));
count = 1;

for N = Ns
    N
   b = rand(N,N) + 1j*rand(N,N);
   b2 = rand(N,N) + 1j*rand(N,N);
   b3 = rand(N,N) + 1j*rand(N,N);
   b4 = rand(N,N) + 1j*rand(N,N);
   b5 = rand(N,N) + 1j*rand(N,N);
   v = 1:N;
%    v = rand(N,N) + 1;
   tic
   for i = 1:its
    c1 = interp2(b,v,v); 
    c1 = interp2(b2,v,v); 
    c1 = interp2(b3,v,v); 
    c1 = interp2(b4,v,v); 
    c1 = interp2(b5,v,v); 
   end
   t1 = toc;
   t_matlab(count) =  t1;
   
   tic
   for i = 1:its
      c2 = splinterp2(b,v,v); 
      c2 = splinterp2(b2,v,v);
      c2 = splinterp2(b3,v,v);
      c2 = splinterp2(b4,v,v);
      c2 = splinterp2(b5,v,v);
   end
   t1 = toc;
   t_cpp(count) = t1; 
   count = count + 1;
end
error = sum(abs(c1(:)-c2(:))) ./ sum(abs(c1(:)))
t_matlab = t_matlab ./ its./5;
t_cpp = t_cpp ./ its./5;
ratios = t_matlab ./ t_cpp
[Ns, ind] = sort(Ns);
ratios = ratios(ind);
figure, plot(Ns,ratios)
out = [Ns' t_matlab' t_cpp'];
csvwrite('benchmark_data.csv',out);