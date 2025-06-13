function [x, iter, err] = graddynpre(A, b, P, x0, toll, nmax)
	[n, m] = size(A);
	if n ~= m
		error("La matrice non e' quadrata")
	end
	if n ~= size(P,1) | n ~= size(P,2)
		error("La matrice P non e' compatibile con A")
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
		z = P\r;
		alpha = (z'*r) / (z'*A*z);
		x = x + alpha*z;
		r = r - alpha*A*z;
		err_k = norm(r)/norm(b);
		err   = [err, err_k];
	end
	if err_k > toll & iter == nmax
		fprintf("Il metodo non converge in %d iterazioni.\n", iter);
	end
