l1 = -100;
l2 = -1;
A = [     0,     1; 
     -l1*l2, l1+l2];
y0 = [1; 1];
h = 1e-4;
t0 = 0;
T  = 5;

f = @(t,y) A*y;

[t_h, U] = eulero_avanti_mat(f,t0,T,y0,h);

% io direi che h < -2/(-l1*l2) && h < -2/(l1+l2)
max(-2/(-l1*l2), -2/(l1+l2));

[t1, y] = ode45(f,[0:h:T],y0);
y = y';

if max(diff(t1)) <= 2/max(abs(eig(A)))
    disp("Limite assoluta stabilita' non superato")
else
    disp("Limite assoluta stabilita' superato")
end

% mica ho capito i punti 3 e 4...

[t2, y2] = ode15s(f,[0:h:T],y0);
y2 = y2';

if max(diff(t2)) <= 2/max(abs(eig(A)))
    disp("Limite assoluta stabilita' non superato")
else
    disp("Limite assoluta stabilita' superato")
end

plot(t_h,  U(1,:),  '-r', ...
     t_h,  U(2,:),  '-g', ...
      t1,  y(1,:), '--b', ...
      t1,  y(2,:), '--k', ...
      t2, y2(1,:), '--m', ...
      t2, y2(2,:), '--y');
