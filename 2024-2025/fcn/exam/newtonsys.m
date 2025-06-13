function [xvect, it] = newtonsys(x0, nmax, toll, f, Jf) 

% x0  : punto di partenza
% nmax: numero massimo di iterazione
% toll: tolleranza sul test d'arresto
% f   : funzione (function handle)
% Jf  : jacobiana

% xvect: vettore contenente le soluzioni ad ogni iterazione
% it   : numero di iterazioni effettuate

it    = 0;
incr  = toll + 1;
xvect = x0;

while(it < nmax && incr >= toll)
    x_old = xvect(:, end); % `end` prende tutte le righe dell'ultima colonna
    delta_x = Jf(x_old) \ f(x_old);
    x_new = x_old - delta_x;
    incr = norm(x_new - x_old);
    xvect = [xvect, x_new];
    it = it+1;
end

fprintf('Numero di iterazioni %d\n', it);
