function I = trapcomp(a,b,M,f)

% Trapezi composita

% a,b: estremi di integrazione
% M: numero di sottointervalli
% f: funzione

% I: valore dell'integrale calcolato

h = (b-a)/M;
x = [a : h : b];
y = f(x);
I = h * sum(y(2:end-1)) + h/2 * (y(1) + y(end));
