function [t_h, U] = eulero_avanti(f, t0, T, y0, h)

% f    : funzione che descrive il problema di Cauchy, f = f(t,y)
% t0, T: estermi dell'intervallo temporale
% y0   : il dato iniziale del problema di Cauchy
% h    : ampiezza del passo di discretizzazione

% t_h  : vettore degli istannti in cui calcoliamo la soluzione discreta
% U    : soluzione discreta calcolata nei nodi temporali t_h

t_h = t0:h:T;
N_istanti = length(t_h);
U = zeros(1, N_istanti);
U(1) = y0;

for i = 2:N_istanti
    U(i) = U(i-1) + h*f(t_h(i-1), U(i-1));
end
