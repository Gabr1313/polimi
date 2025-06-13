function [x, iter, err] = graddyn(A, b, x0, toll, nmax)
	[n, m] = size(A);
	if n ~= m
		error("La matrice non e' quadrata")
	end
	if n ~= size(b, 1)
		error("La matrice non e' compatibile col vettore")
	end

	x = x0;
	iter = 0;
	r = b - A*x;
	err_k = norm(r)/norm(b);
	err   = err_k;

	while err_k > toll && iter < nmax
		iter = iter + 1;
		alpha = (r'*r) / (r'*A*r);
		x = x + alpha*r;
		r = r - alpha*A*r;
		err_k = norm(r)/norm(b);
		err   = [err, err_k];
	end
	if err_k > toll & iter == nmax
		fprintf("Il metodo non converge in %d iterazioni.\n", iter);
	end
