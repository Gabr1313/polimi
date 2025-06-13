function I = simpcomp(a,b,M,f)

% Simpson composita

% a,b: estremi di integrazione
% M: numero di sottointervalli
% f: funzione

% I: valore dell'integrale calcolato

h = (b-a)/M;
x_est = [a : h : b];
x_med = [a + h/2 : h : b - h/2];
y_est = f(x_est);
y_med = f(x_med);
I = h/6 * (y_est(1) + y_est(end) + 2*sum(y_est(2:end-1)) + 4*sum(y_med));
