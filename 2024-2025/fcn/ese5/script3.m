function script3()

f  = @(x) [-x(1) + exp(3*x(2)) - 1; -x(1) + x(1)*x(2)^2 + 2];
Jf = @(x) [         -1, 3*exp(3*x(2));
           -1 + x(2)^2,   2*x(1)*x(2)];

x0 = [1; 0];
[xvect, it] = newtonsys(x0, 1000, 1e-6, f, Jf)
% converge in sole 6 iterazioni
