function [t_h,U,iter_nwt] = eulero_avanti(f,df,t0,T,y0,h)

% Metodo di Eulero all'indietro

% f: funzione ch edescrive il problema di Cauchy, f = f(t,y)
% df: derivata della funzione f
% t0, T: estremi dell'intervallo temporale
% y0: il dato iniziale del problema di Cauchy
% h: ampiezza del passo di discretizzazione temporale

% t_h: vettore degli istanti in cui calcoliamo la soluzione discreta
% U: soluzione discreta calcolata nei nodi temporali t_h
% iter_nwt : vettore contente il numero di iterazioni di Newton per risolvere l'equazione non lineare ad ogni istante temporale

t_h = t0:h:T;
N_istanti = length(t_h);
U = zeros(1,N_istanti);

U(1) = y0;

nmax = 100;
toll = 1e-6;
iter_nwt = zeros(1,N_istanti);

for i = 2:N_istanti
    u_old = U(i-1);
    t_nwt = t_h(i);
    g  = @(x) x - u_old - h*f(t_nwt, x);
    dg = @(x) 1 - h*df(t_nwt, x);
    [xvect, it] = newton(u_old,nmax,toll,g,dg);
    iter_nwt(i) = it;
    U(i) = xvect(end);
end
