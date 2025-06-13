function x = bksub(m, b) 
	assert(isequal(m, triu(m)));
	n = size(m,1);
	x = zeros(n,1);
	for i = n:-1:1
		t = b(i);
		for j = n:-1:i+1
			t = t - x(j) * m(i,j);
		end
		x(i) = t / m(i,i);
	end
