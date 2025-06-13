f = @(x) sin(1 ./ (1 + x.^2));
a = -2*pi;
c =  2*pi;
b = (a+c)/2;

p0 = @(x) (x-b)./(a-b) .* (x-c)./(a-c)
p1 = @(x) (x-c)./(b-c) .* (x-a)./(b-a)
p2 = @(x) (x-a)./(c-a) .* (x-b)./(c-b)

figure(1);
grid = a : (c-a)/1e5 : c;
plot(grid, p0(grid), '-r', ...
     grid, p1(grid), '-g', ...
     grid, p2(grid), '-b');

format short e;
n = 10;
grid2 = a : (c-a)/10 : c
p = polyfit(grid2, f(grid2), n)

figure(2);
plot(grid, f(grid), '-g', ...
     grid, polyval(p,grid), '-r');

errv = abs(f(grid) - polyval(p,grid));
err = max(errv);

figure(3);
plot(grid, errv, '-r');

N = [4;8;10];
tot = size(N,1);
errL = zeros(size(N));
errC = zeros(size(N));
for i = 1:tot;
    n = N(i);

    grid3 = a : (c-a)/n : c;
    p = polyfit(grid3, f(grid3), n);
    errL(i) = max(abs(f(grid) - polyval(p,grid)));

    grid3 = a + (c-a)/2 * (1+cos(-pi : pi/n : 0));
    p = polyfit(grid3, f(grid3), n);
    errC(i) = max(abs(f(grid) - polyval(p,grid)));
end
errL
errC

n = N(3);
grid5 = a + (c-a)/2 * (1+cos(-pi : pi/n : 0));
p = polyfit(grid5, f(grid5), n);
figure(4);
plot(grid, f(grid), '-g',...
    grid, polyval(p, grid), '-r');
figure(5);
plot(grid, abs(f(grid)-polyval(p,grid)), '-r');
