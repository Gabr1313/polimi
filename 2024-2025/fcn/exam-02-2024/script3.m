% idk
% ez

t0 = 0;
y0 = 1;
T  = 5;
f  = @(t, y) -2*y + exp(-2*t) .* sinh(t);
df = @(t, y) -2;
y  = @(t) cosh(t) .* exp(-2*t);
Mt = 100;

[th, uFE] = eulero_avanti(f,t0,t0+T,y0,T/Mt);
[th, uBE] = eulero_indietro(f,t0,t0+T,y0,T/Mt);
[th, uCN] = crank_nicolson(f,df,t0,t0+T,y0,T/Mt);

yex = y(th);

plot(th, yex, '-r', ...
     th, uFE, '-g', ...
     th, uBE, '-b', ...
     th, uCN, '-m');

max_err_FE = max(abs(uFE-yex))
max_err_BE = max(abs(uBE-yex))
max_err_CN = max(abs(uCN-yex));

