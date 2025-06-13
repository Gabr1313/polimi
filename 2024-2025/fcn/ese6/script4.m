fun = @(x) 1 ./ (1 + x.^2);
a = -5;
b =  5;
x_dis = a:0.01:b;
f_dis = fun(x_dis);

n = 5;
x_hat5    = -cos(pi * (0:n) / n);
x_nod5    = (a+b)/2 + (b-a)/2 * x_hat5; % da [-1,1] a [a,b]
f_nod5    = fun(x_nod5);
P5        = polyfit(x_nod5, f_nod5, n);
poly_dis5 = polyval(P5, x_dis);
err5      = abs(f_dis - poly_dis5);

% figure(1);
% plot(x_dis, f_dis, '-r', x_dis, poly_dis5, '--b');
% legend('f(x)', '\Pi^C_5 f(x)');


n = 10;
x_hat10    = -cos(pi * (0:n) / n);
x_nod10    = (a+b)/2 + (b-a)/2 * x_hat10;
f_nod10    = fun(x_nod10);
P10        = polyfit(x_nod10, f_nod10, n);
poly_dis10 = polyval(P10, x_dis);
err10      = abs(f_dis - poly_dis10);

figure(2);
plot(x_dis, f_dis, '-r', x_dis, poly_dis5, '--b', x_dis, poly_dis10, '--m');
legend('f(x)', '\Pi^C_5 f(x)', '\Pi^C_{10} f(x)');

figure(3);
plot(x_dis, err5, 'b', x_dis, err10, 'm');
legend('n=5', 'n=10');
