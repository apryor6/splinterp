clear    
N = 4096^2;
    n = 1;
    vec = 1:.1:N;
    vec = 1:100000;
%     vec = 1:2560;
    vec_c = vec;
    b = rand(N,1) + 1j*rand(N,1);
%     b = rand(N,1);
    xx = 1:N;
    tic
%     for i = 1:n
        c1 = interp1(b,vec);
%     end
    t1 = toc
    
%     for j = 1:10
    tic
%     for i = 1:n
        c2 = splinterp1(b,vec_c);
%     end
    t2 = toc;
    
    speedup = t1./t2
%     end
    sum(abs(c1(:)-c2(:)))
    

% 
% N = 1e8;
% n = 1;
% vec = 1:1024;
% vec_c = vec - 1;
% b = rand(N,1) + 1j*rand(N,1);
% % b = rand(N,1);
% xx = 1:N;
% tic
% for i = 1:n
%     c1 = interp1(b,vec);
% end
% t1 = toc
% 
% tic
% for i = 1:n
%     c2 = splinterp1(b,vec_c);
% end
% t2 = toc
% speedup = t1./t2
% sum(abs(c1(:)-c2(:)))
% 
% 
% 
