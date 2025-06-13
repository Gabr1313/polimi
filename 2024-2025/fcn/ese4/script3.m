n = 47;
T = diag(2*ones(n,1)) + diag(-1*ones(n-1,1), -1) + diag(-1*ones(n-1,1), +1);
F = diag(6*ones(n,1)) + diag(-4*ones(n-1,1), -1) + diag(-4*ones(n-1,1), +1) + diag(ones(n-2,1), -2) + diag(ones(n-2,1), +2);
h = 1/50;
A = T / (h^2) + F / (h^4);

if A == A' & min(eig(A)) > 0
    disp("A e' SDP");
else
    disp("A non e' SDP");
end

P1 = diag(diag(A));
P2 = T/(h^2);
P3 = chol(A);

cA = cond(A)
cP1 = cond(P1\A)
cP2 = cond(P2\A)
cP3 = cond(P3\A)

b = -1*ones(n,1);
x0 = zeros(n,1);
toll = 1e-6;
nmax = 1e5;

[xG  , iterG  , errG]   = graddyn(A,b,x0,toll,nmax);
[xGC , iterGC , errGC]  = gc(A,b,x0,toll,nmax);
[xGP1, iterGP1, errGP1] = graddynpre(A,b,P1,x0,toll,nmax);
[xGP2, iterGP2, errGP2] = graddynpre(A,b,P2,x0,toll,nmax);
[xGP3, iterGP3, errGP3] = graddynpre(A,b,P3,x0,toll,nmax);

figure
loglog(2:iterG  ,errG(2:iterG)    ,'b-x',...
       2:iterGC ,errGC(2:iterGC)  ,'c-x',...
       2:iterGP1,errGP1(2:iterGP1),'k-+',...
       2:iterGP2,errGP2(2:iterGP2),'r-+',...
       2:iterGP3,errGP3(2:iterGP3),'g-+')
legend('Gradiente','GradienteConiugato','P1','P2','P3','location','best')
xlabel('n iter')
ylabel('errore residuo')
grid on
