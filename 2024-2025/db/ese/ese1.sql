-- TODO FAFD (vedi WeBeep esercitazioni)

-- NON SI DEVE FARE
-- `select A, count(*)` senza `group by`
-- `select A, count(*) group by B` se A non e' univoco per B
-- `max(count(*))` aggregati di aggregati
-- `where count(*)` aggregati nella clausola where (violazione dell'ordine
--      temporale: la `where` viene interpretata prima dell'aggregato)
-- `having max(x)` non e' un predicato!
-- `having count(*) = 0` se non c'e' il gruppo, e' vuoto!
-- `count(x1 = x2)`, count puo' prendere in ingresso solo
--      `*`, `[disinct] attr`, `all`
--      `*` conta nache i null
-- clausole where contradditorie

-- Utente (*Codice, Nome, Cognome, Indirizzo, Telefono)
-- Prestito (*Collocazione, *CodUtente, *DataPrestito, DataResa)
-- Copia (*Collocazione, ISBN, DataAcquisizione)
-- DatiLibro (*ISBN, Titolo, AnnoPub, CasaEd, PrimoAut, Genere)

-- Tutti i titoli dei libri acquistati nel 2010
select Titolo
from Copia as C, DatiLibro as D
where C.ISBN = D.ISBN and
    DataAcquisizione between "1-1-2010" and "31-12-2010";
    -- year(DataAcquisizione) = 2010
-- usare il JOIN e' piu' bello

-- Quanti prestiti sono stati fatti?
select count(*) from Prestito;

-- Quanti prestiti di libri gialli
select count(*) from Prestito P join Copia C on P.Collocazione = C.Collocazione
    join DatiLibro D on C.ISBN = D.ISBN
    where Genere = "Giallo";

-- Quanti prestiti ha fatto ogni utente?
select CodUtente, count(*)
from Prestito
group by CodUtente;
-- non e' vero che se raggruppo per qualcosa vada anche messo nella select

-- Idem ma il nome
select Nome, count(*)
from Prestito join Utente on Codice = CodUtente
group by CodUtente, Nome; -- qui non potrei solo mettere il CodUtente
-- nel `group by` potrei anche non mettere `Nome`, ma e' meglio lasciarlo in generale
-- nella `select` senza aggregati metti solo cio' che appare i
--   nella `group by`! (undefined behaviours)

-- Idem ma libri diversi (ISBN)
select Nome, count(disinct ISBN)
from Prestito P join Utente U on U.Codice = P.CodUtente
    join Copia C on P.Collocazione = C.Collocazione
group by CodUtente, Nome;

-- Idem ma libri diversi (Titolo, Autore)

-- Quando e' stato acquisito il primo libro della biblioteca?
select min(DataAcquisizione)
from Copia;

-- Quale e' stato il primo libro acquisito della biblioteca?
select *
from Copia
where DataAcquisizione = (
    -- questa query restituisce un valore scalare, quindi lo posso fare,
    --     altrimenti dovrei usare `in` o `= any`
    select min(DataAcquisizione)
    from Copia
);

-- Quando e' stato publlicato il libro giallo piu' vecchio di ciascuna case editrice
-- che abbia pubblicato almeno 100 libri gialli
select CasaEd, min(AnnoPub)
from DatiLibro
where Genere = "Giallo"
group by CasaEd
having count(*) >= 100;
-- !!! prima si fa la `where` e poi si fa la `having`
-- Quando e' stato publlicato il libro giallo piu' vecchio di ciascuna case editrice
-- che abbia pubblicato almeno 100 libri
select CasaEd, min(AnnoPub)
from DatiLibro
where Genere = "Giallo"
    and CaseEd in (
        select CasaEd
        from DatiLibro
        group by CasaEd
        having count(*) >= 100
    )
group by CasaEd;
-- meglio quella sopra
select CasaEd, min(AnnoPub)
from DatiLibro
where Genere = "Giallo"
group by CasaEd
having CaseEd in (
        select CasaEd
        from DatiLibro
        group by CasaEd
        having count(*) >= 100
    );
-- `having` avviene DOPO il `group by`, `where` avviene PRIMA
--     e' l'unica differenza!

-- Di ogni libro quanti prestiti sono stati fatti? (coll/isbn/titolo)
-- NON VA BENE perche' quelli con count = 0 non vengono selezionati
select count(*), Coll
from Prestito
group by Coll;
-- count(all) altrimenti, altrimenti null conta come 1 (dubito)
select count(all CodUtente), P.Coll
from Prestito P right join Copia C on P.Coll = C.Coll
group by Coll;
-- oppure
select count(*), Coll
from Prestito
group by Coll
    union
select Collocazione, 0 -- NUOVA SINTASSI
from Copia C
where Collocazione not in (
    select Collocazione
    from Prestito
);

-- Numero di prestiti di ogni copia
-- NUOVA SINTASSI
select Collocazione, (
    select count(*) -- deve restituire un valore unitario, per usarlo come attributo
    from Prestito
    where Collocazione = C.Collocazione
) as NumPrestiti, (
    select count(disinct CodUtente)
    from Prestito
    where Collocazione = C.Collocazione
) as NumUtenti
from Copia C;

-- si puo' annidare una query nella clausola from, ma non farlo che al prof non piace
-- usa le viste invece

-- untenti che hanno preso in prestito libri di tutti i generi
select U.Codice, U.Nome, U.Cognome
from Utente U
    join Prestito P on P.CodUtente = U.Codice
    join Copia C on P.Collocazione = D.Collocazione
    join DatiLibro D on C.ISBN = D.ISBN
group by U.Codice, U.Nome, U.Cognome
having count(disinct D.Genere) = (
    select count(disinct Genere)
    from DatiLibro
);

-- durate media dei prestiti (DataResa - DataPrestito)
select avg(DataResa - DataPrestito) -- NUOVA SINTASSI
from Prestito
where DataResa is not null;
-- idem, ma se null diventa today
-- NUOVA SINTASSI coalesce(e1, e2, e3) -> il suo valore e' il primo diverso da null
-- NUOVA SINTASSI Today()
select avg(coalesce(DataResa, Today()) - DataPrestito)
from Prestito;
