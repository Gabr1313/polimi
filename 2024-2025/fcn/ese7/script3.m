f = @(x) x .* sin(x) / (2*pi);
a = 0;
b = 2*pi;
x_plot = [a:0.01:b];
y_plot = f(x_plot);
figure(1)
plot(x_plot, y_plot);

n = 20;
Im = zeros(1,n);
It = zeros(1,n);
Is = zeros(1,n);

for m = 1:n
    Im(m) = pmedcomp(a,b,m,f);
    It(m) = trapcomp(a,b,m,f);
    Is(m) = simpcomp(a,b,m,f);
end

Ie = -ones(1,n);
m = [1:n];


figure(1);
plot(m, Ie, '-k', ... 
     m, Im, 'g--', ... 
     m, It, 'b--' , ...
     m, Is, 'm--' , ...
     'linewidth', 2);
legend('Int. ex', ... 
       'Int. p. medio', ...
       'Int. trap.', ...
       'Int. simp.');

Em = abs(Ie - Im);
Et = abs(Ie - It);
Es = abs(Ie - Is);
h = (b-a) ./ m;

figure(2);
% Se sono proporizionali, in scala logaritmica sono paralleli
loglog(h, Em, 'r--', ...
       h, Et, 'm--', ...
       h, Es, 'k--', ...
       h, h.^2, '-r', ...
       h, h.^4, '-k', ...
       'linewidth', 2);

legend('Err. p. medio', ...
       'Err. trap.', ...
       'Err. simp.', ...
       'h^2', ...
       'h^4');

d2f = @(x) ( 1/(2*pi) * ( 2*cos(x) - x.*sin(x)) );
d4f = @(x) ( 1/(2*pi) * (-4*cos(x) + x.*sin(x)) );

d2f_max = max(abs(d2f(x_plot)));
d4f_max = max(abs(d2f(x_plot)));
toll = 1e-5;
Mm = ceil( ( (b-a)^3 * d2f_max / (  24*toll) ).^(1/2) )
Mt = ceil( ( (b-a)^3 * d2f_max / (  12*toll) ).^(1/2) )
Ms = ceil( ( (b-a)^5 * d4f_max / (2280*toll) ).^(1/4) )

toll
abs(Ie(1) - pmedcomp(a,b,Mm,f))
abs(Ie(1) - trapcomp(a,b,Mt,f))
abs(Ie(1) - simpcomp(a,b,Ms,f))
