A = [ 2, -2,  0;
     -1,  2,  0;
      0, -1,  3];
x = [1, 1, 1].';
b = A*x;

toll = 1e-4;
nmax = 100;
x0 = zeros(size(x));

[xJ, kJ]   = jacobi(A,b,x0,toll,nmax)
[xGS, kGS] = gaussseidel(A,b,x0,toll,nmax)

disp("E' tridiagonale e percio' o entrambi convergono o entrambi non convergono, e nel caso GS converge piu' velocemente di J");
