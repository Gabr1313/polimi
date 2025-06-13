n = 50;
A = diag( 4*ones(n,1))  ....
  + diag(-1*ones(n-1,1),1) + diag(-1*ones(n-1,1), -1) ...
  + diag(-1*ones(n-2,1),2) + diag(-1*ones(n-2,1), -2);
b = 0.2*ones(n, 1);

if (A == A' & min(eig(A)) > 0)
	disp("La matrice e' SDP")
else
	disp("La matrice NON e' SDP")
end

labmda_max = max(eig(A));
labmda_min = min(eig(A));
K = labmda_max / labmda_min

x0 = zeros(n,1);
toll = 1e-5;
nmax = 10000;
[xG, iterG, errG] = graddyn(A, b, x0, toll, nmax);
iterG % dovrebbe uscire 1948

P = diag( 2*ones(n  ,1)) ...
  + diag(-1*ones(n-1,1),-1) + diag(-1*ones(n-1,1),1);
[xGP, iterGP, errGP] = graddynpre(A, b, P, x0, toll, nmax);
iterGP  % dovrebbe uscire 25

% semilogy([0:iterG], errG, "-r", [0:iterGP], errGP, "-b")
% axis([0, 200, 0, 4])
% xlabel("numero di iterazioni")
% ylabel("residuo normalizzato")
% legend("gradiente", "gradiente precodizionato")

alpha_opt = 2 / (max(eig(P \ A)) + min(eig(P \ A)))
[xR, iterR, errR] = richardsonpre(A, b, P, x0, alpha_opt, toll, nmax);
iterR

% `-r` = "red", `-b` = "blue", `-g` = "green"
semilogy([0:iterG], errG, "-r", [0:iterGP], errGP, "-b", [0:iterR], errR, "-g")
axis([0, 200, 0, 4])
xlabel("numero di iterazioni")
ylabel("residuo normalizzato")
legend("gradiente", "gradiente precodizionato", "richardson precodizionato")
