y_ex = @(t) t ./ (1 + t.^2);
t0 = 0;
T = 10;
t_plot = t0:0.01:T;

% figure(1);
% plot(t_plot, y_ex(t_plot));
% title('Soluzione analitica');

f = @(t,y) 1 ./ (1+t.^2) - 2*y.^2;
y0 = 0;

h1 = 0.2;
[EA1_t_h, EA1_U] = eulero_avanti(f,t0,T,y0,h1);
h2 = 0.05;
[EA2_t_h, EA2_U] = eulero_avanti(f,t0,T,y0,h2);

figure(2)
plot(t_plot , y_ex(t_plot), '-k' , ...
     EA1_t_h, EA1_U       , '--r', ...
     EA2_t_h, EA2_U       , '--b');
legend('Soluzione analitica', 'Soluzione EA h=0.2', 'Soluzione EA h=0.05');

h1 = 0.2;
[EI1_t_h, EI1_U, EI1_it_pf] = eulero_indietro(f,t0,T,y0,h1);
h2 = 0.05;
[EI2_t_h, EI2_U, EI2_it_pf] = eulero_indietro(f,t0,T,y0,h2);

figure(3)
plot(t_plot , y_ex(t_plot), '-k' , ...
     EI1_t_h, EI1_U       , '--r', ...
     EI2_t_h, EI2_U       , '--b');
legend('Soluzione analitica', 'Soluzione EI h=0.2', 'Soluzione EI h=0.05');

figure(4)
plot(EI1_t_h, EI1_it_pf, 'o:');
xlabel('istanti');
ylabel('numero iterazioni di punto fisso');

H = [0.2, 0.1, 0.05, 0.025, 0.0125];
errore_EA = [];
errore_EI = [];

for h = H
    [EA_t_h, EA_U] = eulero_avanti(f,t0,T,y0,h);
    [EI_t_h, EI_U, EI_it_pf] = eulero_indietro(f,t0,T,y0,h);
    errore_EA = [errore_EA, max(abs(y_ex(EA_t_h) - EA_U))];
    errore_EI = [errore_EI, max(abs(y_ex(EI_t_h) - EI_U))];
end

figure(5)
loglog(H, errore_EA, '-or', ...
       H, errore_EI, '-ob', ...
       H, H, '--k', ...
       H, H.^2, '--m');
legend('errore EA', 'errore EI', 'ordine 1', 'ordine 2');
