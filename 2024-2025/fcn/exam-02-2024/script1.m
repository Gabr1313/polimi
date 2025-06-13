n = 6;
A = hilb(n);
if A == A' & min(eig(A)) > 0
    disp('SDP')
else
    disp('non SDP')
end

eu = true;
for i = 1:n-1
    d = abs(det(A(1:i,1:i)));
    eu = eu & d > 1e-14;
end
if eu
    disp('La fattorizzazione LU esiste ed e` unica');
else
    disp('Non e` vero che la fattorizzazione LU esiste ed e` unica');
end

n = 10;
A = hilb(n) + 20*eye(n);
x = ones(n,1);
b = A * x;

D = diag(diag(A));
E = -tril(A,-1);
F = -triu(A,+1);

bJ   = D \ (D-A);
rohJ = max(abs(eig(bJ)))
rJ   = -log(rohJ)

x0         = zeros(n,1);
toll       = 1e-12;
nitmax     = 1e5;
[xJ, kJ]   = jacobi(A,b,x0,toll,nitmax);
true_err_J = norm(xJ-x,2)
est_err_J  = rohJ^kJ * norm(xJ-x0,2)

bGS   = (D-E) \ F;
% rhoGS = max(abs(eig(bGS))) % Sbagliato, bGS non e' SDP
c = norm(bGS,2);
rGS   = -log(rohGS)

[xGS, kGS]  = gaussseidel(A,b,x0,toll,nitmax);
true_err_GS = norm(xGS-x,2)
est_err_GS  = c^kGS * norm(xGS-x0,2)
