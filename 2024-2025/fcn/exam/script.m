n = 10;
A = diag( 3*ones(n,1)) + diag(-2*ones(n-1,1),1) + diag(-1*ones(n-1,1), -1);
xEX = [1:n]';
b = A*xEX

[L, U, P] = lu(A);
figure(1);
spy(L);
figure(2);
spy(U);

x = bksub(U, fwsub(L, P*b))

B = A * A';
[L, U, P] = lu(B);
if P == eye(n)
    disp("Non e' stato eseguito pivoting");
else
    disp("E' stato eseguito pivoting");
end

x = B \ b

condB = cond(B)
r = b - B*x
err_rel_stima = condB * norm(r,2)/norm(b,2)
