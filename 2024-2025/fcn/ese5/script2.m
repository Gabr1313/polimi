function script2()

phi1 = @(x) cos(x);
a  = 0;
b  = 1.5;
x0 = 0.3;
nit = 7;
% xn = ptofis_visual(a, b, x0, nit, phi1); %TODO: uncomment
% come mi aspetto dalla teoria il metodo converge al punto fisso

phi2 = @(x) x.^2 + x - 1;
a  = -1.3;
b  =  1.1;
x0 =  0.98;
nit = 10;
% xn = ptofis_visual(a, b, x0, nit, phi2); %TODO: uncomment
% come mi aspetto dalla teoria, la convergenza del metodo non e' garantita per entrambi i punti
% per x1=-1 il metodo sembra convergere molto lentamente, mentre per x2=1 sembra non convergere

phi3 = @(x) x - phi1(x)
nmax = 1000;
toll = 1e-6;
x0   = 0.3;
[xvect, it] = ptofis(x0, nmax, toll, phi3);
