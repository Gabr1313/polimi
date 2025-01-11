-- ORDINE ESECUZIONE: from - where - group by - having (sui gruppi) - select

-- ingrediente(idingr, nome, kcalpergrammo)
-- piatto(idpiatto, nome, prezzo)
-- ricetta(idpiatto, nome, quantita)
-- ordine(idordine, idpiatto, idstudente, dataord, oraord, coordinatediconsegna, orarioeffettivodiconsegna)
-- studente(idstudente, cognome, nome, citta')

-- di default va quasi sempre bene
-- on delete no action
-- on update cascade

-- nome e id dei piatti piu' calorici
select nome, idpiatto, sum(quantita * kcalpergrammo)
from ricetta natural join ingrediente natural join piatto
group by idpiatto
having sum(quantita * kcalpergrammo) >= all (
    select sum (quantita * kcalpergrammo)
    from R natural joinn ingrediente
    group by IdPiatto
)
;

-- nome degli studenti che hanno ordinato al massimo 2 diversi tipi di piatti
-- contenti solo ingredienti con un numero di calorie per grammo superiore a 2
create view ppp (idpiatto) as
select idpiatto
from ricetta natural join ingredienti
group by idpiatto
having min(kcalpergrammo) >= 2
;

select nome, idstudente
from ordine natural join ppp natural join studente
group by idstudente
having count(distinct idpiatto) < 3
;
-- attento: chi non ha mai fatto ordini dovrebbe essere considerato?

-- primo ordine per ogni piatto
select idpiatto, dataord, oarord
from ordine O
where not exists (
    select * 
    from ordine P
    where P.idpiatto = O.idpiatto and (
         P.data < O.data or 
         (P.data = O.data and P.ora < O.ora)
    )
)
;

select idpiatto, dataord, oarord
from ordine
except 
select O.idpiatto, O.dataord, O.oraord
from ordine O join ordine P on O.idpiatto = P.idpiatto
where O.data > P.data or (O.data = P.data and O.ora > P.ora)
;

-- area(idarea, latitudine, longitudine, tipoterreno)
-- animal(idanimale, nome, datanascita, specie, sesso)
-- guide(idguida, nome, datanascita, qualifica)
-- osservazione(idanimale, data, ora, idarea, idguida, note)

-- le osservazioni di una guida nello stesso giorno sono al massimo su 5 tipi di terreno
create assertion PochiTipiDiTerreno as (check (
    not exists (
        select idguida
        from osservazioni natural join area
        group by idguida, data
        having count(distinct tipoterreno) > 5
    )
))
;

-- seleziona la zona preferita da ogni specie
create view QuantiAvvistamentiPerArea as 
select IdArea, Specie, count(*) as NumAvv
where data between "1-11-22" and "31-12-2022"
from osservazione natural join animale
group by IdArea, Specie
;

select *
from QuantiAvvistamentiPerArea22 Q
where NumAvv = (
    select max(NumAvv)
    from QuantiAvvistamentiPerArea22
    where Specie = Q.Specie
)
;

-- nomi delle guide che hanno effettuato osservazioni di un leone e una giraffa
-- appena nati, nello stesso giorno
select G.Nome, AL.Nome, AG.Nome, OL.Data
from guida G 
     natural join (Osservazione OL natural join Animale AL)
     join (Osservazione OG natural join Animale AG) on G.IdGuida = Og.IdGuida
where AL.Specie = "Leone"
  and AG.Specie = "Giraffa"
  and OL.Data = AL.DataNascita
  and OG.Data = AG.DataNascita
  and OG.Data = OL.Data
;

-- @todo COME SI FACEVA NEI LINGUAGGI FORMALI AD ESPRIMERE UNA QUERY CHE ESTRARE
-- GLI ANIMALI CHE SONO STATI OSSERVATI IN TUTTE LE AREE?
