function [x, k] = richardson(A, b, x0, alpha, toll, nmax)
	n = size(b, 1);
	if (size(A,1) ~= n || size(A,2) ~= n || size(x0, 1) ~= n)
		error("Le dimensioni sbagliate")
	end

	x = x0;
	res = b - A*x;
	for k = 0:nmax
		if (norm(res) / norm(b) <= toll)
			return
		end
		x = x + alpha*res;
		res = b - A*x;
	end
