function [x, k] = gaussseidel(A, b, x0, toll, nmax)
	n = size(b, 1);
	if (size(A,1) ~= n || size(A,2) ~= n || size(x0, 1) ~= n)
		error("Le dimensioni sbagliate")
	end
	% TODO: non penso serva, ma devo invece verificare che (D-E) sia invertibile
	if (prod(diag(A)) == 0)
		error("Elementi sullad diagonale = 0")
	end

	D = diag(diag(A));
	E = -tril(A,-1);
	F = -triu(A, 1);

	B_gs = (D-E) \ F;
	f_gs = (D-E) \ b;
	x = x0;

	for k = 0:nmax
		if (norm(b - A*x) / norm(b) <= toll)
			k = k;
			return
		end
		x = B_gs * x + f_gs;
	end
