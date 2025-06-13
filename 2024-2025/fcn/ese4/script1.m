n = 7;
A = diag( 9*ones(n,1))  ....
  + diag(-3*ones(n-1,1),1) + diag(-3*ones(n-1,1), -1) ...
  + diag(   ones(n-2,1),2) + diag(   ones(n-2,1), -2)
b = [7 4 5 5 5 4 7]'

labmda_max = max(eig(A));
labmda_min = min(eig(A));
alpha_lim = 2 / labmda_max
alpha_opt = 2 / (labmda_min + labmda_max)

x0 = zeros(n,1);
toll = 1e-6;
nmax = 1000;
alpha1 = 2;
% siccome alpha1 > alpha_lim il metodo diverge
[xR1, kR1] = richardson(A, b, x0, alpha1, toll, nmax)

alpha1 = 0.11;
[xR2, kR2] = richardson(A, b, x0, alpha1, toll, nmax)

[xR3, kR3] = richardson(A, b, x0, alpha_opt, toll, nmax)
