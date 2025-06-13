y0 = 10;
dt = 0.1;
T  = 1;
t0 = 0;
yS = [10.0;9.92;9.79;9.55;9.23;8.77;8.20;7.52;6.80;6.01;5.10];
g = 9.81;

f = @(t) y0 - 1/2 * g * t.^2;
grid = t0: (T-t0)/(size(yS,1)-1) :T;

p = polyfit(grid, yS, size(yS,1)-1);

thingrid = t0: (T-t0)/1e5 :T;;
plot(thingrid, f(thingrid), '-g',...
     thingrid, polyval(p,thingrid), '-r',...
     thingrid, interp1(grid, yS, thingrid), '-b');

plot(thingrid, abs(f(thingrid) - polyval(p,thingrid)), '-r',...
     thingrid, abs(f(thingrid) - interp1(grid, yS, thingrid)), '-b');

t2 = 1.05;
real = f(t2)
poly = polyval(p,t2)
disp("interp1 cannot");
