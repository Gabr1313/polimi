f  = @(y, t) (2*y + (t.*y).^2) ./ -t;
y0 = 1;
t0 = 1;
T  = 5;
h  = 0.2;

[tH1, U1] = eulero_avanti(f,t0,T,y0,h);
U1

yEX = @(t) 1 ./ (t.^2 .* (1 + log(t)));

h = 0.1;
[tH2, U2] = eulero_avanti(f,t0,T,y0,h);
U2

figure(1);
plot(tH1, yEX(tH1), '-g', ...
     tH1, U1, '-r', ...
     tH2, U2, '-b');

figure(2);
plot(tH1, yEX(tH1), '-g', ...
     tH2, U2, '-b');

disp("Con h=0.2 la soluzione e' non asintoticamente stabile... e nemmeno con h=0.1");

h = [0.1, 0.05, 0.025, 0.0125]
n = size(h, 2);
err = zeros(1, n);
figure(4);
styles = {'-r', '-g', '-b', '-k', '-m'};
for i = 1:n;
    [tH, U] = eulero_avanti(f,t0,T,y0,h(i));
    err(i) = max(abs(U - yEX(tH)));
    plot(tH, U, styles{mod(i-1, numel(styles)) + 1});
    hold on;
end

% TODO: this is strange... really strange
figure(3);
loglog(h, err);
