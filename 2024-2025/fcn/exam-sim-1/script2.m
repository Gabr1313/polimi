f = @(x) 4 * cos(pi/4*x) - exp(-4*x);
a = -1;
b =  1;
I = 32/pi * sin(pi/4) - 2*sinh(4)/4 

n = [5,10,20,40];
err = zeros(size(n));
for i = 1:size(n,2)
    Ii = trapcomp(a,b,n(i),f)
    err(i) = max(abs(Ii - I));
end

format short e;
err

disp("Ovviamente al diminuire di h diminuisce l'errore, nel caso dei trapezi e' O(h^2)");

loglog(n, err,'-r', ...
       n,(b-a)./n.^2,'-g');

g = @(x) -2*x + 3;

err = zeros(size(n));
for i = 1:size(n,2)
    Ii = trapcomp(a,b,n(i),g)
    err(i) = max(abs(Ii - I));
end

disp("Essendo un polinomio del primo ordine, viene approssimato con esattezza dalla formula dei trapezi composita");
