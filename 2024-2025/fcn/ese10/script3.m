f = @(x) atan(x) ./ (7 + sin(7*x));
a = 0; b = pi;
xdis = linspace(a,b,1000);
xL = linspace(a,b,4);
pL = polyfit(xL, f(xL), 3)

xMQ = linspace(a,b,100);
yMQ = f(xMQ);
pMQ = polyfit(xMQ,yMQ,1)


plot(xdis, f(xdis), '-b', ...
     xdis, polyval(pL, xdis), '-r', ...
     xdis, polyval(pMQ, xdis), '-g', ...
     xL, f(xL), 'ko');
