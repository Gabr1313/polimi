function [x, k] = jacobi(A, b, x0, toll, nmax)
	n = size(b, 1);
	if (size(A,1) ~= n || size(A,2) ~= n || size(x0, 1) ~= n)
		error("Le dimensioni sbagliate")
	end
	if (prod(diag(A)) == 0)
		error("Elementi sullad diagonale = 0")
	end

	D = diag(diag(A));
	E = -tril(A,-1);
	F = -triu(A, 1);

	B_j = D \ (D-A);
	f_j = D \ b;
	x = x0;

	for k = 0:nmax
		if (norm(b - A*x) / norm(b) <= toll)
			return
		end
		x = B_j * x + f_j;
	end
