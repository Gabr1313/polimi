function m = matBuild(n)
	m = diag(-1*ones(n  ,1) ,  0) ...
	  + diag( 1*ones(n-1, 1), -1);
	m(1, : ) = 1;

