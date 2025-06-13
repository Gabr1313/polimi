function [xvect, it] = newton(x0, nmax, toll, fun, dfun) 

% x0  : punto di partenza
% nmax: numero massimo di iterazione
% toll: tolleranza sul test d'arresto
% fun : funzione (function handle)
% dfun: derivata della funzione (function handle)

% xvect: vettore contenente le soluzioni ad ogni iterazione
% it   : numero di iterazioni effettuate

it    = 0;
incr  = toll + 1;
xvect = x0;

while(it < nmax && incr >= toll)
    x_old = xvect(end); % `end` prende l'ultimo elemento
    if (dfun(x_old) == 0)
        error('La derivata e` zero, non posso dividere, aiuto')
    end
    x_new = x_old - fun(x_old) / dfun(x_old);
    incr = abs(x_new - x_old);
    xvect = [xvect; x_new];
    it = it+1;
end
