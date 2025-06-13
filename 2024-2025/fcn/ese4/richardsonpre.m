function [x, k, err] = richardsonpre(A, b, P, x0, alpha, toll, nmax)
	n = size(b, 1);
	if (size(A,1) ~= n || size(A,2) ~= n || size(x0, 1) ~= n)
		error("Le dimensioni sbagliate")
	end
	if n ~= size(P,1) | n ~= size(P,2)
		error("La matrice P non e' compatibile con A")
	end

	x = x0;
	res = b - A*x;
	err = norm(res)/norm(b);
	for k = 0:nmax
		if (norm(res) / norm(b) <= toll)
			return
		end
		z = P\res;
		x = x + alpha*z;
		res = b - A*x;
		err_k = norm(res)/norm(b);
		err = [err, err_k];
	end
