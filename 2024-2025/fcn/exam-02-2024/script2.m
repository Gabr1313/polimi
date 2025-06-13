% k di Q_Mh: per ogni polinomio P di ordine k, I(P) = Q_Mh(P)
% 1: vero,  grado di esattezza 3, polinomio di ordine 2 (dovrei fare i calcoli dove espando l'integrale e la formula dell'approssimazione...)
% 2: falso, grado di esattezza 1, polinomio di ordine 2 " "
% 3: idk

a = -1;
b =  1;
f    = @(x) x - exp(2*x) + 1;
I    = 2 - sinh(2);
M_h  = 2.^[0:10];
n = size(M_h, 2);

err_TM_vec = zeros(1,n);
err_PM_vec = zeros(1,n);
err_CS_vec = zeros(1,n);
h_vec = zeros(1,n);

for i = 1:n
    h_vec(i)      = (b-a)/M_h(i);
    err_TM_vec(i) = abs(trapcomp(a,b,M_h(i),f) - I);
    err_PM_vec(i) = abs(pmedcomp(a,b,M_h(i),f) - I);
    err_CS_vec(i) = abs(simpcomp(a,b,M_h(i),f) - I);
end

format short e;
h_vec
err_TM_vec
err_PM_vec
err_CS_vec
