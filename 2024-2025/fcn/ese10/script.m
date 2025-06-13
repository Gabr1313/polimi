f = @(x) x - atan(exp(x) - 1);
dfun = @(x) 1 - exp(x) ./ (1 + (exp(x) - 1).^2);

a = -1;
b =  2;
x = linspace(a,b,1000);

nmax = 100;
toll = 1e-8;
x0A  = 3;
x0B  = 0.2;

[xA, itA] = newton(x0A, nmax, toll, f, dfun);
[xB, itB] = newton(x0B, nmax, toll, f, dfun);
xA(end)
xB(end)

figure(1);
plot(x,           f(x),  '-b', ...
     x, zeros(size(x)), '--k', ...
     xA(end),        0,  'or', ...
     xB(end),        0,  'or');

[pA, cA] = stimap(xA);
[pB, cB] = stimap(xB);

% Wierd behaviour... even though I should obtain the same result (rounding problems)
% it is enough to decrease precision
dfun2 = @(x) 1 - 1 ./ (1 + (exp(x) - 1).^2) .* exp(x);
[xB2, itB2] = newton(x0B, nmax, toll, f, dfun2);
[pB2, cB2] = stimap(xB2);
