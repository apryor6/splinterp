% Ns = [2.^(4:9)]
clear
Ns = [25:25:400]
Ns = 128;
count=1;
for N = Ns;
    N
%     N = 256;

    b = rand(N,N,N)+1j*rand(N,N,N);
%     b = rand(N,N,N);

    [xx,yy,zz] = meshgrid(1:N,1:N,1:N);
    [xx_o,yy_o,zz_o] = meshgrid(2:(N-1),2:(N-1),5);
    
%     xx_o = repmat(xx_o(:),[1,1]);
%     yy_o = repmat(yy_o(:),[1,1]);
%     zz_o = repmat(zz_o(:),[1,1]);
    
    xx_oc = xx_o - 1;
    yy_oc = yy_o - 1;
    zz_oc = zz_o - 1;
    tic
    for it = 1:1
    a = interp3(b,xx_o,yy_o,zz_o);
    end
    t1(count) = toc;

    tic
    for it = 1:1
    a1 = splinterp3(b,xx_oc,yy_oc,zz_oc);
    end
    t2(count) = toc;

    
    count = count+1;
end
sum(abs(a(:)-a1(:)))
ratios = t1./t2
