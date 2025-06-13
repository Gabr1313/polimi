% eTM <= (b-a)/12 * max(f"(x)) * h^2 = (b-a)^3 / 12 * max(f"(x))
% ePM <= (b-a)/24 * max(f"(x)) * h^2 = (b-a)^3 / 24 * max(f"(x))

% qTM non e' corretta (ordine 1)
% qCS e' corretta     (ordine 3)
% qGL non l'abbiamo fatto

f = @(x) sin(3*x) .* exp(-x);
a = -pi;
b = +pi;
Ireal = -3/5 * sinh(pi);
Mh = 2.^[0:10];
n = size(Mh,2);

errTMvec = zeros(1,n);
errPMvec = zeros(1,n);
errCSvec = zeros(1,n);

for i = 1:n
    errTMvec(i) = abs(Ireal - trapcomp(a,b,Mh(i),f));
    errPMvec(i) = abs(Ireal - pmedcomp(a,b,Mh(i),f));
    errCSvec(i) = abs(Ireal - simpcomp(a,b,Mh(i),f));
end

format short e;
((b-a)./Mh)
errTMvec
errPMvec
errCSvec
