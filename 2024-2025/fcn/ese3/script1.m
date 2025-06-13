function script1()
	n = 7;
	A = diag(9*ones(n,1)) ...
		- diag(3*ones(n-1,1),1)  - diag(3*ones(n-1,1),-1) ...
		+ diag(ones(n-2,1),2) + diag(ones(n-2,1),-2)
	% numero di zeri
	nnz_elem = nnz(A)
	% A e' a dominanza diagonale?
	if ( 2*abs(diag(A)) - sum(abs(A), 2) > 0 )
		disp('La matrice e` a dominanza diagonale per right')
	end
	% A e' sdp?
	if (A == A' & min(eig(A)) > 0)
		disp('La matrice e` sdp')
	end

	D = diag(diag(A))
	E = -tril(A,-1)
	F = -triu(A, 1)
	% Bj = inv(D) * (D-A)
	B_j  = D \ (D-A) % piu' precisione dell'inversa
	B_gs = (D-E) \ F
	roh_j = max(abs(eig(B_j)))
	roh_gs = max(abs(eig(B_gs)))
	% essendo roh > 1 => condizione necessaria e sufficiente per convergenza OK

	b = [7 4 5 5 5 4 7]'
	[x, k] = jacobi(A, b, zeros(n,1), 1e-6, 100)
	[x, k] = gaussseidel(A, b, zeros(n,1), 1e-6, 100)
	[x, k] = richardson(A, b, zeros(n,1), 0.1, 1e-6, 100)
	A \ b
