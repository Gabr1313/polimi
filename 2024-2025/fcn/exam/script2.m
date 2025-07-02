f = @(x) (x-2) .* exp(x-1);
alpha = 2;
a = 1;
b = 3;
grid = a:(b-a)/1e5:b;
figure(1);
plot(grid, f(grid));
grid on;

phi = @(x) x - ((x-2).*exp(x-2)) ./ (2*exp(1)-1);
figure(1);
plot(grid, phi(grid), '-k', grid, grid, '--b');
grid on;

x0 = 1.5;
toll = 1e-4;
nmax = 1000;
[xvect, n] = ptofis(x0, nmax, toll, phi);
n
x1 = xvect(2)
x2 = xvect(3)
dif = diff(xvect)

stimap(xvect)
