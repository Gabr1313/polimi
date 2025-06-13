fun = @(x) 1 ./ (1 + x.^2);
a = -5;
b =  5;
x_dis = a:0.01:b;
f_dis = fun(x_dis);

n = 5;
x_nod5    = linspace(a,b,n+1);
f_nod5    = fun(x_nod5);
p5        = polyfit(x_nod5,f_nod5,n); % array di coefficienti
poly_dis5 = polyval(p5,x_dis);

% figure(1);
% plot(x_dis, f_dis, '-r', x_dis, poly_dis5, '--b');
% title('Interpolazione su nodi equispaziati');
% legend('f(x)', '\Pi_5 f(x)');

err5 = abs(f_dis - poly_dis5);

% figure(2)
% plot(x_dis, err5, 'r');
% title('Errore di Interpolazione');

n = 10;
x_nod10    = linspace(a,b,n+1);
f_nod10    = fun(x_nod10);
p10        = polyfit(x_nod10,f_nod10,n)
poly_dis10 = polyval(p10,x_dis);

figure(3);
plot(x_dis, f_dis, '-r', x_dis, poly_dis5, '--b', x_dis, poly_dis10, '--m');
title('Interpolazione su nodi equispaziati');
legend('f(x)', '\Pi_5 f(x)', '\Pi_{10} f(x)');

err10 = abs(f_dis - poly_dis10);

figure(4)
plot(x_dis, err5, 'b', x_dis, err10, 'm');
title('Errore di Interpolazione');
legend('n = 5', 'n = 10');
