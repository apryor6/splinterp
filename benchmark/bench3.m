clear
addpath ../
its = 10;
Ns = 10:10:8192;
Ns = 256;
t_matlab = zeros(1,numel(Ns));
t_cpp = zeros(1,numel(Ns));
count = 1;
% Ns = 256;

for N = Ns
    N
   b = rand(N,N,N) + 1j*rand(N,N,N);
   v = 1:N;
   v = 1 + rand(N,N)*N/2;
   tic
   for i = 1:its
      c1 = interp3(b,v,v,v); 
   end
   t1 = toc;
   t_matlab(count) = t_matlab(count) + t1;
   
   tic
   for i = 1:its
      c2 = splinterp3(b,v,v,v); 
   end
   t1 = toc;
   t_cpp(count) = t_cpp(count) + t1; 
   count = count + 1;
end
error = sum(abs(c1(:)-c2(:))) ./ sum(abs(c1(:)))
t_matlab = t_matlab ./ its;
t_cpp = t_cpp ./ its;
t_matlab./t_cpp
out = [Ns' t_matlab' t_cpp'];
csvwrite('benchmark_data.csv',out);

