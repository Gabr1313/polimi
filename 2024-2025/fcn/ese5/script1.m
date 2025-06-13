function script1()

x = linspace(-2, 2, 1001);
fun = @(x) exp(x) - x.^2  - sin(x) - 1;
y = fun(x);
figure(1);
plot(x, y, '-b') % '-b' = blue
grid on
hold on % mi permette di disegnare un'altra figura
plot(x, zeros(length(x),1), '-r'); % '-r' = red
xlabel('x');
ylabel('y');
title('y = f(x)');

dfun = @(x) exp(x) - 2*x - cos(x);
dy = dfun(x);
figure(2);
plot(x, dy, '-b');
hold on
grid on
plot(x, zeros(length(x),1), '-r');
xlabel('x');
ylabel('y');
title('y = d/dx f(x)');

d2fun = @(x) exp(x) - 2 + sin(x);
d2y = d2fun(x);
figure(3);
plot(x, d2y, '-b');
hold on
grid on
plot(x, zeros(length(x),1), '-r');
xlabel('x');
ylabel('y');
title('y = d^2/dx^2 f(x)');

% per x1 mi aspetto che newton converga con ordine 1: la derivata prima li si annulla (non e' una radice semplice)
% mentre per x2 mi aspetto ordine 2, siccome e' una radice semplice

x1 = 0;
[xvect, it] = newton(0.1, 1000, 1e-6, fun, dfun);
% non ho scritto io "stima p"
[p, c]  = stimap(xvect);
% come mi asettavo il metodo converge localmente in x1 = 0 con ordine 1 (ha molteplicita' 2)
errore = abs(xvect - x1);
figure(4)
semilogy([1:it+1], errore, 'b*') % "blue con l`asterisco"
xlabel('iterazioni')
ylabel('errore')
title('Convergenza lineare per Newton in x1=0')


x2 = 1.27970133100099;
[xvect, it] = newton(1.2, 1000, 1e-6, fun, dfun);
% non ho scritto io "stima p"
[p, c]  = stimap(xvect);
% come mi asettavo il metodo converge localmente in x1 = 0 con ordine 1 (ha molteplicita' 2)
errore = abs(xvect - x2);
figure(5)
semilogy([1:it+1], errore, 'b*') % "blue con l`asterisco"
xlabel('iterazioni')
ylabel('errore')
title('Convergenza lineare per Newton in x2=1.27')





