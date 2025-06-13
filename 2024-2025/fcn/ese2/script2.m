function script2(n)
	N = zeros(1, int32(log2(n)));
	for i = 1:size(N,2)
		N(i)=2^i;
	end
	err_rel  = zeros(1, size(N, 2));
	res_norm = zeros(1, size(N, 2));
	condi    = zeros(1, size(N, 2));

	% ch = chol(h);
	% y2 = fwsub(ch.', b);
	% x2 = bksub(ch, y2);

	for i = 1:size(N,2)
		h = hilb(N(i));
		x = ones(N(i), 1);
		b = h * x;
		[lo, up, perm] = lu(h);
		y2 = fwsub(lo, perm*b);
		x2 = bksub(up, y2);
		err_rel(i)  = norm(x2 - x) / norm(x);
		res_norm(i) = norm(b - h*x2) / norm(b);
		condi(i) = cond(h);
	end

	loglog(N, err_rel, '-s', N, res_norm, '-o', N, condi, '-x');
	legend('errore relativo', 'residuo normale', 'condizionamento');
	xlabel('size n');
	ylabel('err, r, K');
	grid on;
