f  = @(x) (x-1).^2 .* log(x) - (x-1);
df = @(x) 2*(x-1) .* log(x) + (x-1).^2 ./ x - 1;
a = 0.3;
b = 2.2;

figure;
grid = a : (b-a)/1e4 : b;
plot(grid, f(grid));
grid on;

disp("Newton non ha problemi siccome e' C1, quindi converge localmente");
disp("Le iterazioni di punto fisso sono consistenti: phi(x) = f(x) + x => (phi(x) = x <=> f(x) = 0). In 1 la derivata e' zero, e quindi converge localmente con ordine > 1");

nmax = 1000;
x0 = 0.7;
toll = 1e-5;
phi = @(x) f(x) + x
sol = 1;

[xN, itN] = newton(x0,nmax,toll,f,df);
[xP, itP] = ptofis(x0,nmax,toll,phi);
stimap(xN);
stimap(xP);
semilogy(0:itN, abs(xN - sol), '-r',...
         0:itP, abs(xP - sol), '-b');
grid on;
