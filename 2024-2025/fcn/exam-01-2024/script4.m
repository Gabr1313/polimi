% vedi teoria --> T([a,b]) in [a,b] && abs(T(x)-(T(y))) < abs(x-y) per ogni x,y in [a,b]
% se T'(x) < 1 per ogni x in [a,b] => il fattore asintotico di riduzione e' T'(alpha)
% x_n+1 = x_n - g(x_n)/g'(x_n)
% T'(x) = 1 - ( (f'(x))^2 - f(x)*f"(x) ) / (f'(x))^2 = f(x)*f"(x) / (f'(x))^2 = 0 <=> x = alpha (&& x != 0)
% T"(alpha)/2

g = @(x) sin(x) ./ (1 + x.^2);
a = pi-2;
b = pi+2;
alpha  = pi;
lambda = - (1 + pi^2);
T = @(x) x - lambda * g(x);

% x = [a: 0.01 : b];
% plot(x, T(x), "r")

itmax = 100;
toll  = 1e-15;
x0    = 5;
[xv, it] = ptofis(x0,100,toll,T)
format short e;
p = stimap(xv);
p(end)
