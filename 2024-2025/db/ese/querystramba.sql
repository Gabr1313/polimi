use querystramba;

create table Prestito (
    coll char(10),
    data date,
    codUtente int,
    primary key(data, coll)
);

create table Copia (
    coll char(10) primary key
);

insert into Copia values
    ("scaf-1"),
    ("scaf-2"),
    ("scaf-3"),
    ("scaf-4")
;

insert into Prestito values
    ("scaf-1", "1-1-1", 100),
    ("scaf-2", "1-1-2", 100),
    ("scaf-2", "1-1-3", 200);

select count(codUtente), C.coll
from Prestito P right join Copia C on P.Coll = C.Coll
group by C.Coll;

select count(coalesce(codUtente,-1)), C.coll
from Prestito P right join Copia C on P.Coll = C.Coll
group by C.Coll;

-- select count(D.codUtente), D.coll
-- from (
--     select coalesce(codUtente,-1) codUtente, C.coll
--     from Prestito P right join Copia C on P.Coll = C.Coll
-- ) as D
-- group by D.coll;
