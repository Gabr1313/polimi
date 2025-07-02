f = @(x) (1 - 2*x) .* exp(-2*x);
a = 0;
b = 1;
n = 1;
I = quadcomp(a,b,n,f)

f0 = @(x) x.^0;
f1 = @(x) x.^1;
f2 = @(x) x.^2;
f3 = @(x) x.^3;
f4 = @(x) x.^4;

e0 = abs(1   - quadcomp(a,b,n,f0))
e1 = abs(1/2 - quadcomp(a,b,n,f1))
e2 = abs(1/3 - quadcomp(a,b,n,f2))
e3 = abs(1/4 - quadcomp(a,b,n,f3))
e4 = abs(1/5 - quadcomp(a,b,n,f4))

Iex = exp(-2);
format short e;
N = [5;10;20;40];
sz = size(N,1);
err = zeros(sz,1);
for i = 1:sz
    err(i) = abs(Iex - quadcomp(a,b,N(i),f));
end
err

figure(1)
loglog(N, 1./(N.^3), '--r', ...
       N, 1./(N.^4), '--g', ...
       N, 1./(N.^5), '--b', ...
       N, err, '-k');
