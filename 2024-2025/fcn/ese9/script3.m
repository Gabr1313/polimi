u_ex = @(t) 10*exp(-3*t + 1 ./ (2*t + 1));
t0   = 0;
T    = 10;
t_dis = linspace(t0,T,1000);
figure(1);
plot(t_dis,u_ex(t_dis));

f = @(t,y) -y * (3 + 2./(2*t + 1).^2);
h = 1;
y0 = 10*exp(1);
[t_h, U] = eulero_avanti(f,t0,T,y0,h);
U(5);
U(9);

figure(2);
plot(t_dis, u_ex(t_dis), '-k', ...
     t_h, U, '--r');
 
% in questo esercizio lamda_segnato = max(df/dy) = df/dy (1) = 5 => h < 2/5

H = [0.1, 0.05, 0.025, 0.0125];
err = [];
for h = H
    [tH, U] = eulero_avanti(f,t0,T,y0,h);
    err = [err, max(abs(u_ex(tH) - U))];
end
figure(3);
loglog(H,  err, 'ro-', ...
       H,    H, '--k', ...
       H, H.^2, '--b');
