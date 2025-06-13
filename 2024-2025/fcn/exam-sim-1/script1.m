A = [ 2, -1,  0;
     -1,  3,  1;
      0, -1,  4];
x = [1/2, 1/3, 1/4].';
b = A*x;

toll = [1e-2, 1e-3, 1e-4];
nmax = 100;
x0 = zeros(size(x));

for t = toll
    [xJ, kJ] = jacobi(A,b,x0,t,nmax);
    xJ
    kJ
end

disp("dovrei fare cose dove stimo l'errore, o semplicemente dire: per avere maggiore precisione devo fare piu' iterazioni?");

toll = 1e-4;
[xGS, kGS] = gaussseidel(A,b,x0,toll,nmax);
xGS
kGS

D = diag(diag(A));
E = -tril(A,-1);
F = -triu(A, 1);
bJ   = D \ (E+F);
rhoJ = max(abs(eig(bJ)))
bGS   = (D-E) \ F;
rhoGS = max(abs(eig(bGS)))
disp("Come si nota, sia rhoJ, rhoGS < 0, condizione necessaria e sufficiente per la convergenza.");
disp("Inoltre siccome rhoGS < rhoJ, il primo converge piu' velocemente: e_(n+1) < rho * e_(n)");
