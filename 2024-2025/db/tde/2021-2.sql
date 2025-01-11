create table Somministrazione (
	IDVaccino int,
	CFPaziente varchar,
	Data date,
	NomeCentro varchar,
	primary key (IDVaccino, CFPaziente, Data),
	foreign key (IDVaccino)
		references Vaccino(IDVaccino)
			on update cascade
			on delete no action,
	foreign key (CFPaziente)
		references Paziente(CF)
			on update cascade
			on delete no action,
	foreign key (NomeCentro)
		references Centro(Nome)
			on update cascade
			on delete no action,
	check (
		(select Regione
		from Centro C
		where Nome = NomeCentro)
		=
		(select Regione
		from Paziente P
		where P.CF = CFPaziente)
	)
);

select V.IDVaccino, count(*) numVaccinati
from Paziente P, Vaccino V
where P.DataNascita < '19-2-1941' and V.DosiRichieste = (
	select count(*)
	from Somministrazione S
	where S.CFPaziente = P.CF and V.IDVaccino = S.IDVaccino
)
group by V.IDVaccino;

select C.Nome
from Centro C
where not exists (
	select *
	from Somministrazione S join Paziente P on S.CFPaziente = P.CF
	where S.NomeCentro = C.Nome and S.IDVaccino = "PoliVax" and P.cittaResidenza <> C.Citta
);
