t0    = 0;
T     = 6;
u_ex  = @(t) 0.5 * asin((exp(4*t) - 1) ./ (exp(4*t) + 1));
t_dis = linspace(t0, T, 1000);

figure(1);
plot(t_dis, u_ex(t_dis));
title('Sol. analitica');

y0 = 0;
f  = @(t,u) cos(2*u);
df = @(t,u) -2 * sin(2*u);

h = 0.5;
[thEA, uEA] = eulero_avanti(f,t0,T,y0,h);
[thEB, uEB] = eulero_indietro(f,df,t0,T,y0,h);
[thCN, uCN] = crank_nicolson(f,df,t0,T,y0,h);

figure(2);
plot(t_dis, u_ex(t_dis), '-r', ...
      thEA,         uEA, '-g', ...
      thEB,         uEB, '-b', ...
      thCN,         uCN, '-k');

H = [0.4, 0.2, 0.1, 0.05, 0.025, 0.0125];
E1 = [];
E2 = [];
E3 = [];

for h = H
    [t1, u1] = eulero_avanti(f,t0,T,y0,h);
    [t2, u2, it_nwt2] = eulero_indietro(f,df,t0,T,y0,h);
    [t3, u3, it_nwt3] = crank_nicolson(f,df,t0,T,y0,h);
    E1 = [E1, max(abs(u_ex(t1) - u1))];
    E2 = [E2, max(abs(u_ex(t1) - u2))];
    E3 = [E3, max(abs(u_ex(t1) - u3))];
end

figure(3);
loglog(H,   E1, 'ro-', ...
       H,   E2, 'bo-', ...
       H,   E3, 'go-', ...
       H,    H, '--k', ...
       H, H.^2, '--m');
