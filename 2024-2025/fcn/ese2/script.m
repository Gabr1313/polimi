function script(n)
	err_rel = zeros(n,1);
	res_norm = zeros(n,1);
	cond_A = zeros(n,1);
	for i = 1:n
		A = matBuild(i);
		[lo, up, perm] = lu(A);
		assert(isequal(perm, eye(i)));

		b = zeros(i, 1);
		b(1) = 2;

		y = fwsub(lo, b);
		x = bksub(up, y);
		x_real = 2/i * ones(i, 1);

		err_rel(i) = norm(x - x_real) / norm(x_real);
		res_norm(i) = norm(b - A*x) / norm(b);
		cond_A(i) = cond(A);
	end

	semilogy(1:n, err_rel, '-s', 1:n, res_norm, '-o', 1:n, cond_A, '-x');
	legend('errore relativo', 'residuo normale', 'numero di condizionamento');
	% xlabel('size n');
	% ylabel('');
	grid on;
