f = @(t,y) -1./t .* (2*y + (t.^2).*(y.^2))
t0 = 1;
T  = 5;
y0 = 1;
h = 0.2;

[tH1, U1] = eulero_avanti(f,t0,T,y0,h)
yEX = @(t) 1 ./ (t.^2 .* (1 + log(t)));

h = 0.1;
[tH2, U2] = eulero_avanti(f,t0,T,y0,h);

figure(1);
xGrid = t0 : (T-t0)/1e5 : T;
plot(xGrid, yEX(xGrid), '-g', ...
       tH1,         U1, '-r', ...
       tH2,         U2, '-b');

disp('h < => precisione >');

H = [0.1, 0.05, 0.025, 0.0125]';
it = size(H,1);
err = zeros(1,it);
for i = 1:it
    [tH, U] = eulero_avanti(f,t0,T,y0,H(i));
    err(i) = max(abs(U - yEX(tH)));
end

figure(2);
loglog(H, err, '-r', ...
       H, H, '-g');
grid on;
err
disp("Wiiii, dovremmo avere che l'errore si e` O(h) e quindi che si dimezzi a ogni passo");
