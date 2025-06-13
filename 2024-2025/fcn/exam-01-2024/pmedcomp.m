function I = pmedcomp(a,b,M,f)

% Formula di punto medio composita

% a,b: estremi di integrazione
% M: numero di sottointervalli
% f: funzione

% I: valore dell'integrale calcolato

h = (b-a)/M;
x = [a + h/2 : h : b - h/2]; % punti medi
I = h * sum(f(x));
