% y'(t) = -l*y(t), y(t0) = 1 
% u_t+1 < L*u_t dove 0 < L < 1 per ogni t > t*
% u_t+1 = u_t + h * y'(t+1) = u_t - h * l * u_t+1 => u_t+1 = u_t / (1 + h*l) => 1 / (1 + h*l) < 1 sempre siccome h,l > 0

t0 = 0;
T  = 8;
y0 = 0; % il testo dice y0 = 1, ma sbaglia
Mt = 1000;
f  = @(t,y) -2*y + 5*cos(5*t)*exp(-2*t);
df = @(t,y) -2;
y  = @(t) sin(5*t) .* exp(-2*t);

[t_h, uFE] = eulero_avanti(f,t0,t0+T,y0,T/Mt);

[t_h, uBE] = eulero_indietro(f,t0,t0+T,y0,T/Mt);

[t_h, uCN] = crank_nicolson(f,df,t0,t0+T,y0,T/Mt);
yex = y(t_h);

max_err_FE = max(abs(yex - uFE))
max_err_BE = max(abs(yex - uBE))
max_err_CN = max(abs(yex - uCN))

plot(t_h, uFE, "r", ...
     t_h, uBE, "g", ...
     t_h, uCN, "m", ...
     t_h, yex, "b");
