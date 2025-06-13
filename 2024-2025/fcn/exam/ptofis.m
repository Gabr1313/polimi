function [xvect, it] = ptofis(x0, nmax, toll, phi) 

% x0  : punto di partenza
% nmax: numero massimo di iterazione
% toll: tolleranza sul test d'arresto
% phi : funzione di punto fisso
% dfun: derivata della funzione (function handle)

% xvect: vettore contenente le soluzioni ad ogni iterazione
% it   : numero di iterazioni effettuate

it    = 0;
incr  = toll + 1;
xvect = x0;

while(it < nmax && incr >= toll)
    x_old = xvect(end); % `end` prende l'ultimo elemento
    x_new = phi(x_old)
    incr = abs(x_new - x_old);
    xvect = [xvect; x_new];
    it = it+1;
end

fprintf('Numero di iterazioni %d\n', it);
fprintf('Punto fisso calcolato: %12.13f (last_delta = %12.13f)\n', xvect(end), incr);
