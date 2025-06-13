function [xvect,it] = newton(x0,nmax,toll,fun,dfun)

% Metodo di Newton per la ricerca di radici della funzione fun

% x0: punto di partenza
% nmax: numero massimo di iterazioni
% toll: tolleranza sul test d'arresto
% fun: funzione (function handle)
% dfun: derivata della funzione (function handle)

% xvect: vettore contenente le soluzioni ad ogni iterazione
%        (l'ultima componente è la soluzione)
% it: numero di iterazioni effettuate

% Inizializzazione
it = 0;
incr = toll + 1;
xvect = x0;

while(it < nmax && incr >= toll)
    xv = xvect(end);
    if(dfun(xv) == 0)
        disp('Arresto per annullamento di dfun')
        break
    else
        xn = xv - fun(xv)/dfun(xv);
        incr = abs(xn - xv);
        xvect = [xvect; xn];
        it = it + 1;
    end
end
