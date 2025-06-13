n = 6;
A = gallery('dramadah', n);
A(:,n) = 0;
A
x = true;
for i = 1:n-1
    d = det(A(1:i,1:i))
    x = x && abs(d) > 1e-10;
end
x

[l, u, p] = lu(A)

n = 10
A = gallery('dramadah', n);
A = A + A' + 5*eye(n);
A
x = ones(n,1)
b = A*x

x0 = zeros(n,1);
toll = 1e-12;
nitmax = 10000;
stop_test = 1;

D = diag(diag(A));
BJ = D \ (D - A)
rhoJ = max(abs(eig(BJ)))
rJ = -log(rhoJ) % Velocita' di convergenza asintotica? not sure
[xJ, kJ] = jacobi(A,b,x0,toll,nitmax)
est_err_J = rhoJ^kJ * norm(x)
true_err_J = norm(abs(xJ-x),2)

D = diag(diag(A));
E = -tril(A,-1);
F = -triu(A,+1);
BGS = (D-E) \ F
rhoGS = max(abs(eig(BGS)))
rGS = -log(rhoGS) % Velocita' di convergenza asintotica? not sure
[xGS, kGS] = gaussseidel(A,b,x0,toll,nitmax)
est_err_GS = rhoGS^kGS * norm(x)
true_err_GS = norm(abs(xGS-x),2)
