% f([a,b]) in [a,b] ed esiste L < 1 tale che |f(x1)-f(x2)| < L|x1-x2| per ogni x1,x2 in [a,b]
% |x_(k+1) - alpha| / |x_k - alpha|^2 < f"(alpha)/2

% guarda la derivata di T1(x) e noti che in una e' = 3/2, nell'altro 1/2. Solo nel secondo converge

T1 = @(x) x - 1/2 * (x^2 - 1) / (x^2 + 1)
itmax = 100;
toll  = 1e-5;
x0    = 0

[xv, it] = ptofis(x0,itmax,toll,T1);
format short e;
stimap(xv);
eC = 1-xv(end)

% guarda la derivata di T1(x) e noti che in una e' = 1/2, nell'altro 3/2. Solo nel primo converge

T2 = @(x) -x - 1/2 * (x^2 - 1) / (x^2 + 1)
[xv, it] = ptofis(x0,itmax,toll,T2);
format short e;
stimap(xv);
eC = -1-xv(end)
