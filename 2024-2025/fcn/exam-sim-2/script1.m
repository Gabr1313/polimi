n = 7;
A = diag(ones(n,1));
A(:,n) = ones(n,1);
A(n,:) = 1:n;
A

[l, u, p] = lu(A)
figure(1);
spy(A, 'r');
figure(2);
spy(l, 'g');
figure(3);
spy(u, 'b');

(p^-1)*l*u

disp("Si, c'e' stato fill-in, ma non saprei come dire se sia stato eseguito pivoting semplicemente usando il comando spy"); % TODO

b = zeros(n, 1);
b(1) = 1;
x = bksub(u,fwsub(l,p*b));
A*x

for n = [20,30,40]
    A = diag(ones(n,1));
    A(:,n) = ones(n,1);
    A(n,:) = ones(1,n);
    A(n,1) = 1.1;
    xEX = -(1.1 / (1.1+n-3)) * ones(n,1);
    xEX(1) = 1 + xEX(1);
    xEX(end) = -xEX(end);

    [l, u, p] = lu(A);
    b = zeros(n, 1);
    b(1) = 1;
    x = bksub(u,fwsub(l,p*b));
    err_rel = norm(x - xEX) / norm(xEX)
end
