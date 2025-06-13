f = @(x) exp(sin(x)) .* cos(x);
a = 0;
b = pi/2;

n = 20;
M = [1:n];

Im = zeros(1,n);
Is = zeros(1,n);

for i = 1:n
    Im(i) = pmedcomp(a,b,M(i),f);
    Is(i) = simpcomp(a,b,M(i),f);
end

Ie = (exp(1)-1) * ones(1,n);
figure(1)
plot(M, Ie, '-k', ... 
     M, Im, 'g--', ... 
     M, Is, 'm--' , ...
     'linewidth', 2);
legend('Int. ex', ... 
       'Int. p. medio', ...
       'Int. simp.');

Em = abs(Ie - Im);
Es = abs(Ie - Is);
h = (b-a) ./ M;

figure(2);
% Se sono proporizionali, in scala logaritmica sono paralleli
loglog(h, Em, 'r--', ...
       h, Es, 'k--', ...
       h, h.^2, '-r', ...
       h, h.^4, '-k', ...
       'linewidth', 2);

legend('Err. p. medio', ...
       'Err. simp.', ...
       'h^2', ...
       'h^4');
