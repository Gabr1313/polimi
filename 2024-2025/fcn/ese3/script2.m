function script2()
	n = 100;
	R1 = ones(n,1);
	R2 = 2*ones(n,1);
	A = diag(-R2) + diag(R1(1:n-1),-1);
	A(1,:) = 1;

	Bin = [R1, -R2];
	d   = [-1, 0  ];
	Asp = spdiags(Bin, d, n, n);
	Asp(1,:) = 1;
	
	% get memory occupied
	whos A Asp
