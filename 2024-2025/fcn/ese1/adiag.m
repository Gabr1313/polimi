function ris = adiag(a)
	n = size(a);
	if n(1) ~= n(2)
		error('errore la matrice non è qudrata!')
	end
	dim = n(1);
	for i = 1:dim
		ad(i) = a(i, dim-i+1);
	end
	ad
