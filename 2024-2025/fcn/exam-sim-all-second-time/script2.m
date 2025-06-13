it = [5, 10, 20, 40]';
a = -1;
b =  1;
f = @(x) 4*cos(pi*x/4) - exp(-4*x);
Iex = 32/pi * sin(pi/4) - sinh(4)/2

n = size(it,1);
err = zeros(n,1);

format short e;

I = zeros(n,1);
for i = 1:n
    I(i) = trapcomp(a,b,it(i),f);
    err(i) = abs(Iex - I(i));
end
I
err

disp('Oh, wow, con un intervallo piu` piccolo ottengo un risultato piu` preciso, incredibile');
figure(1);
h = (b-a)./it;
loglog(h, err,    '-r', ...
       h,   h,    '-g', ...
       h,   h.^2, '-b');

f = @(x) -2*x + 3;
I = zeros(n,1);
for i = 1:n
    I(i) = trapcomp(a,b,it(i),f);
end
I

disp('Siccome `f` e` un polinomio di primo grado, viene approssimato perfettamente dall`integrale numerico che usa il metodo dei trapezi composito');
