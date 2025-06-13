function x = fwsub(m, b) 
	assert(isequal(m, tril(m)));
	n = size(m,1);
	x = zeros(n,1);

	% for i = 1:n
	% 	t = b(i);
	% 	for j = 1:i-1
	% 		t = t - x(j) * m(i,j);
	% 	end
	% 	x(i) = t / m(i,i);
	% end

	x(1) = b(1) / m(1,1);
	for i = 2:n
		x(i) = (b(i) - m(i,1:i-1) * x(1:i-1)) / m(i,i);
	end
