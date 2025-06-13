A = [2, -1, 0;
    -1,  3, 1;
     0, -1, 4];
xEX = [1/2, 1/3, 1/4]';
b = A*xEX;
x0  = [0, 0, 0]';
nmax = 100;
toll = [1e-2, 1e-3, 1e-4]';
n = size(toll, 1);
xJ = zeros(size(xEX,1),n);
kJ = zeros(n,1);

for i = 1:n
    [xJ(:,i), kJ(i)] = jacobi(A,b,x0,toll(i),nmax);
end
xJ
kJ

disp('minore tolleranza => maggiore precisione');

[xGS, kGS] = gaussseidel(A,b,x0,toll(end),nmax)

disp('dominanaza diagonale stretta => J e GS convergono, inoltre GS converge piu` velocemente siccome la matrice e` tridiagonale');

D = diag(diag(A));
E = D - tril(A);
F = D - triu(A);
rohJ  = max(eig(D \ (E+F)))
rohGS = max(eig((D-E) \ F)) 
