---
documentclass: article
geometry: margin=0.5in
---

```matlab
constants();

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

iSAT = 1e-9;
iS   = 0.1;
R    = 20;

xa = 0.4;
xb = 0.5;
xx = xa : (xb-xa)/10000 : xb;

A  = 2/3 * R * iSAT;
B  = A + R * iS/3;
g1 = @(x) x;
g2 = @(x) B - A * exp(x./Vth);
g  = @(x) g1(x) - g2(x);

figure(1);
plot(xx, g1(xx), '-b', ...
     xx, g2(xx), '-r');

x0 = 0;
format long e;
xEX = fzero(g, x0)

Tg  = @(x) Vth * log((B-x)./A);
dTg = @(x) -Vth / (B-x);
W   = abs(dTg(xEX))

x0    = 0;
itMAX = 1000;
toll  = 1e-12;
[x ,nIT, err] = fixed_point(x0,Tg,toll,itMAX);
% stimap(x);
xFIX    = x(end)
estERR  = err(end)
trueERR = xEX - xFIX

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

C = 1e-6;
t0 = 0;
tf = 0.1;
iSf = 0.1;
f   = 100;
tD  = 1e-2;
x0  = 0;
iS  = @(t) iSf * sin(2*pi*f * t) .* exp(-t ./ tD);

f = @(t,x) (-3*x) ./ (2*R*C) + (iSAT/C) * (1 - exp(x ./ Vth)) + iS(t) ./ (2*C);
[tm,xm] = ode15s(f,[t0,tf],x0);
deltaXa = max(xm) - min(xm)

dfdx   = @(t,x) -3 ./ (2*R*C) - iSAT/(C*Vth) * exp(x ./ Vth);
NT     = 1000;
tol    = 1e-12;
maxtit = 100;
[tth,xth,iter_nwt] = crank_nicolson(f,dfdx,t0,tf,x0,(tf-t0)/NT);
deltaXb = max(xth) - min(xth)

figure(2);
plot(tm, xm, '-r', ...
     tth, xth, '-b');
legend('ode15s', 'crank\_nicolson');
```
