n = 7;
A = eye(n);
A(:,end) = ones(n,1);
A(end,:) = 1:n;
A
[L, U, P] = lu(A)
disp('Basta guardare P per notare che sia stato eseguito pivoting: P != I');
figure(1);
spy(A,'g');
hold on;
spy(L,'ro');
hold on;
spy(U,'bo');
disp('E` stato eseguito fill-in');

b = zeros(n,1);
b(1) = 1;

% PAx = LUx = Pb
% Ly = Pb
% Ux = y 
x = bksub(U, fwsub(L, P*b))

N = [20,30,40]';
it = size(N,1);
err = zeros(it,1);
errREL  = zeros(it,1);
for i = 1:it
    n = N(i);
    A = eye(n);
    A(:,end) = ones(n,1);
    A(end,:) = [1.1, ones(1,n-1)];
    b = [1;zeros(n-1,1)];
    xEX = (-1.1/(1.1 + n - 3)) * ones(n,1);
    xEX(1) = 1 + xEX(1);
    xEX(end) = -xEX(end);
    [L, U, P] = lu(A);
    x = bksub(U, fwsub(L, P*b));
    err(i) = max(abs(x-xEX));
    errREL(i) = norm(x-xEX)/norm(xEX)
end
err
errREL
