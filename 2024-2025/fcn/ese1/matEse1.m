function m = matEse1()
	% n = 7;
	% m = zeros(n, n);
	% x = [1, -3, 6, -3, 1];
	% for i = 1:n 
	% 	for j = 1:length(x) 
	% 		if i-3+j > 0 & i-3+j <= n
	% 			m(i, i-3+j) = x(j);
	% 		end
	% 	end
	% end
	% m(n,n) = 9;

	n = 7;
	m = diag( 6*ones(n,  1),  0) + ...
	    diag(-3*ones(n-1,1),  1) + ...
	    diag(-3*ones(n-1,1), -1) + ...
	    diag(   ones(n-2,1),  2) + ...
	    diag(   ones(n-2,1), -2);
	m(n,n) = 9;

