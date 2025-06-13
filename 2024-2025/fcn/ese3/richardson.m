function [x, k] = richardson(A, b, x0, alpha, toll, nmax)
	n = size(b, 1);
	if (size(A,1) ~= n || size(A,2) ~= n || size(x0, 1) ~= n)
		error("Le dimensioni sbagliate")
	end

	% uglier
	% B_r = eye(n) - alpha * A;
	% f_r = alpha*b;
	% x = x0;
	% for k = 1:nmax
	% 	x = B_r * x + f_r;
	% 	if (norm(b - A*x) / norm(b) <= toll)
	% 		return
	% 	end
	% end

	x = x0;
	res = b - A*x;
	for k = 0:nmax
		if (norm(res) / norm(b) <= toll)
			return
		end
		x = x + alpha*res;
		res = b - A*x;
	end
