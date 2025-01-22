/*
create database lezione;
*/
use lezione

/*  _   _ _____ ___ _    ___
 * | | | |_   _|_ _| |  / __|
 * | |_| | | |  | || |__\__ \
 *  \___/  |_| |___|____|___/
 */

/*
source file.sql;
show tables;
select * from `table`;
show columns from `table`;
select * from information_schema.referential_constraints;
-- .referential_constraints
-- .domains
-- .domain_constrains
-- .tables
-- .views
-- .columns
-- ognuna con varie viste
*/

/*   ___ ___ ___   _ _____ ___
 *  / __| _ \ __| /_\_   _| __|
 * | (__|   / _| / _ \| | | _|
 *  \___|_|_\___/_/ \_\_| |___|
 */

create table Domini (
    -- [var]char [(`len`)] [char set `family`]
    a varchar (6), -- char set `family` ??
    -- [var]bit  [(`len`)]
    b bit,
    -- numeric [(`precision`[,`scale`])]
    c numeric,     -- `scale` ??
    -- decimal [(`precision`[,`scale`])]
    d decimal,
    -- int
    e int,
    -- smallint
    f smallint,
    -- float [(`precision`)]
    g float(4),
    -- double
    h double,
    -- real
    i real,
    -- date(`month`, `day`, `year`) -- ? ("YYYY-MM-DD")
    j date,
    -- time [(`precision`)][with time zone]:(`hour`, `minute`, `second`) -- ??
    k time,        -- with time zone ??
    -- timestamp[(`precision`)][with time zone] `timezone hour` `timezone minute`
	-- usage: timestamp("2017-07-23",  "13:10:11"); 
    l timestamp,   -- with time zone ??
    -- ??  interval `x` [to `y`]
	-- x interval hour to milliseconds
    -- boolean (true of false)
    n boolean,
    -- bigint
    o bigint,
    -- blob
    p blob,
    -- ?? clob
	-- enum
	q enum('foo', 'bar')
);

-- create domain `name` as `elementar domain` [`default` `x`][`constraints`]
-- `x` = <`generic value` | user | null> -- user è la login utente
-- create domain PrezzoQuotidiani as decimal(3) default 1.50 not null;
-- ??

-- create table `name` (
--     `attribute name` `domain` [`default`] [`constraints`],
--     `attribute name` `domain` [`default`] [`constraints`],
--     [`constraints`]
-- );
-- `constraints` intra-relazionali:
--     not null
--     primary key                -- dopo il dominio
--     primary key(`attr`, `...`) -- alla fine
--     unique                     -- ~primary eky
--     check (`query`)
create table Studente (
    Matr    char(6)     primary key,
    Nome    varchar(30) not null,
    Cognome varchar(30) not null,
    Citta   varchar(20),
    CSS     char(3),
    unique(Nome, Cognome)
);

create table Corso (
    CodCorso char(6)    primary key,
    Titolo varchar(30)  not null,
    Docente varchar(20)
);

create table Esame (
    Matr          char(6),
    CodCorso      char(6),
    Data date     not null,
    Voto smallint not null,
    primary key (Matr,CodCorso),
    -- Integrità referenziale: problema degli Orfani:
    -- foreign key (`attr`)
    --     references `table`
    --        on delete <cascade | set null | set default | no action>
    --        on update <cascade | set null | set default | no action>
    foreign key (Matr)
        references Studente
            on delete cascade
            on update cascade,
    foreign key (CodCorso)
        references Corso
            on delete no action -- impedisce la modifica
            on update set default
);

-- index: per accedere più velocemente alla tabella
-- create [unique] index `name` on `tab`(`attr`)
create unique index codIdx on Corso(CodCorso);

/*  _____ _   _ ___ _    ___ ___
 * |_   _| | | | _ \ |  | __/ __|
 *   | | | |_| |  _/ |__| _|\__ \
 *   |_|  \___/|_| |____|___|___/
*/

-- insert into `table` [(`attr, ...`)] <values | query>
insert into Studente (Matr, Nome, Cognome, Citta, CSS) values
    (123, "Carlo"  , "X", "Bologna", "Inf"),
    (415, "Paola"  , "X", "Torino" , "Inf"),
    (702, "Antonio", "X", "Roma"   , "Ges");

create table Bolognesi (
    Matr    char(6)     primary key,
    Nome    varchar(30) not null,
    Cognome varchar(30) not null,
    Citta   varchar(20),
    CSS     char(3),
    unique(Nome, Cognome),
    -- ?? assert Cognome == "Bologna"
    foreign key (Matr)
        references Studente
            on update cascade
            on delete cascade
);
insert into Bolognesi
    select * from Studente where Citta = "Bologna";

insert into Corso values
    (1, "matematica" , "Secchi"),
    (2, "informatica", "Campi" ),
    (3, "barzellette", "Io"    );

-- delete from `table` [where `condition`]
delete from Corso where Docente = "Io";

insert into Esame values
    (123, 1, "2011-9-7" , 30),
    (123, 2, "2011-1-22", 28),
    (702, 2, "2011-9-7" , 20);

/*  __  __  ___  ___ ___ _____   __
 * |  \/  |/ _ \|   \_ _| __\ \ / /
 * | |\/| | (_) | |) | || _| \ V /
 * |_|  |_|\___/|___/___|_|   |_|
*/
-- update `table`
--     set `attr` = <`expr` | `query` | null | default>
--      [, `attr` = <`expr` | `query` | null | default> , `...`]
--     [where `condizione`]
update Esame
    set Voto = Voto - 2
    where data = "2011-9-7";

-- alter table `tab_name` add column `...`
alter table Studente add column hobby char(30);
-- alter table `name` alter column `col_name` add `...`
alter table Studente modify column hobby char(30) default "non ne ha";
-- alter table `name` drop column `col_name` add `...`
alter table Studente drop column hobby;
-- drop table `tab_name` [cascade] -- cascade distrugge qualsiasi cosa faccia
--                                    riferimento a questa table
drop table Domini;
-- drop index `idx_name`
drop index codIdx on Corso;

/*   ___  _   _ ___ _____   __
 *  / _ \| | | | __| _ \ \ / /
 * | (_) | |_| | _||   /\ V /
 *  \__\_\\___/|___|_|_\ |_|
*/
-- select `attr`
-- from `tab`
-- where `condition`

-- SELECT
-- select *
-- select distinct `attr` -- rimuove duplicati
-- select `attr` as `alias`
-- select `math_operation(attr)` as `alias`
-- select sum(`attr`)

-- FROM
-- from `table`
-- from `table` as `alias`
-- from `table1`, `table2`, `...`
-- from `table1` join `table2` on `table1.x=table2.y`

-- WHERE
-- where `boolean expression`
--     `attr1` =  `val`
--     `attr1` <> `val` -- diverso
--     and
--     or
-- where `attr` between `val_min` and `val_max`
-- where `attr` like `"fake_regex"`
--     in fake_regex '%' = "qualsiasi stringa" e '_' = "qualsiasi carattere"
-- where `attr` is [not] null
--     Logica a 3 valori: True, False, Unknown
--     X not null == X = `a` or X <> `a`

select * from Studente;
select Nome, Cognome from Studente where CSS = 'Inf';
select * from Studente where
    Citta = "Roma" and (CSS like "I%" or CSS like "G_s");

-- DISTINCT
select          CSS from Studente;
select distinct CSS from Studente;

-- JOIN
-- join implicito
select distinct Nome from Studente, Esame, Corso
    where Studente.Matr = Esame.Matr and Esame.CodCorso = Corso.CodCorso
        and Titolo like "mat%" and Voto = 30;
-- join esplicito
-- select `attr` [, `...`]
--     from `table` [[`join_type`] join `table` on `condition`] [where `...`]
select distinct Nome from Studente
    join Esame on Studente.Matr = Esame.Matr
    join Corso on Esame.CodCorso = Corso.CodCorso
    where Titolo like "mat%" and Voto = 30;

select distinct Nome from Studente join Esame join Corso
    on Studente.Matr = Esame.Matr and Esame.CodCorso = Corso.CodCorso
    where Titolo like "mat%" and Voto = 30;
-- tipo di join:
--     inner (default)
--     left  (se left  non matchati, li include con NULL sui campi di right)
--     right (se right non matchati, li include con NULL sui campi di left )
--     full  (right + left)
-- altri tipi:
--     natural (attributi con lo stesso nome devono coincidere)

-- AS
-- select `attr` [[as] `alias`] [, ...] from `table` [[as] `alias`] [, ...]
select distinct X.nome from Studente as X, Esame as Y
    where X.Matr = Y.Matr and Y.Voto = 30;

-- QUERY CON ORDINAMENTO
-- order by `attr` [<asc | desc>] [, `attr` [<asc | desc>]]
-- ovviamente gli `attr` di `oder by` appartengono a quelli della `select`
select * from Esame order by Voto;
select * from Esame order by Voto desc, Data asc;

-- QUERY CON AGGREGAZIONE
--     count(<* | [distinct | all] attr [, attr]>)
--     all considera tutti i valori diversi da `null`
--     (`all` è di default, ma mettilo che i prof sono felici quando potrebbero
--      esserci valori nulli)
select count(distinct Matr) from Esame;
--     <sum | max | min | avg>([distinct | all] attr [, attr])
--     posso anche fare operazioni all'interno di () con gli attributi
select sum(distinct matr) from Esame;
-- secondo il prof non si può fare!
select distinct Nome, max(Matr) from Studente;
-- ma invece dovrei scrivere
select distinct Nome, Matr from Studente
        where Matr = (select max(Matr) from Studente);

-- QUERY CON RAGGRUPAMENTO
-- select `...` from `...` [where `...`]
--     [group by `...`] [having `...`] [ordered by `...`]
select Matr, sum(Voto) from Esame
    group by Matr having count(*) >= 2;
-- query scorretta: quale voto prendo? è ambiguo
select S.Matr, E.voto, count(*)
    from Studente S join Esame E
    on (S.Matr = E.Matr)
    group by S.Matr;

-- QUERY BINARIE
-- `query` <union [all] | except [all] | intersect>`query`
--     `all` include i duplicati
select Nome from Studente where Citta like "B%"
    union all -- se duplicate, ripete le tuple
    select Nome from Studente where CSS = "Inf";

select Nome from Studente where CSS = "Inf"
    except all -- matcha i duplicati, se dalla prima ne avanzano li stampa
    select Nome from Studente where Citta like "B%";

-- QUERY NIDIFICATE
-- select `...` from `...` where `expr` (`query`)
-- dove `expr` del tipo:
--     `attr` <= | <> | < | <= | > | >= > <any | all>
--     [(] `attr` [, `...`)] [, `...`] <in | not in >
--     <exists | not exsists > -- nella `query` conviene usare `select *`
-- `in`     == `= any`
-- `not in` == `<> all`
select distinct Nome, Matr from Studente
        where Matr in (select max(Matr) from Studente);
select distinct Nome, Matr from Studente
        where Matr >= all (select max(Matr) from Studente);
-- si possono anche riferire attributi esterni nella query nidificate (binding)
-- devono avere lo stesso schema!
select Nome from Studente S1 where not exists (
    select Nome from Studente S2 where
        S1.Matr <> S2.Matr
        and S1.Nome = S2.Nome
);

-- VISIBILITÀ
-- sopra e sotto ok, sullo stesso livello no (controlla... fai esercizi)

/* __   _____ _____      __
 * \ \ / /_ _| __\ \    / /
 *  \ V / | || _| \ \/\/ /
 *   \_/ |___|___| \_/\_/
*/
-- le `view` sono simili a delle `select`: permettono di accedere a porzioni
-- ristrette di una `table`, come fossero puntatori
-- le `view` si possono usare ovunque va una `query`, quindi anche in `update`
-- modificando la tabella principale (come fossero dei puntatori)

-- create view `name`[(`attr` `, ...`)] as `query` [with [local | cascade] check option]
create view Torinesi as
    select Matr, Nome, Cognome
    from Studente
    where Citta = "Torino";
select citta
from Torinesi;
-- ! non si possono metteri operandi aggregati nidificati (es: `avg(count*)`)
-- ma meglio usare le viste
create view CittaNumStudenti(Citta, NumStudenti) as
    select Citta, count(*)
    from Studente
    group by(Citta);
select avg(NumStudenti) from CittaNumStudenti;

-- o alternativamente al prof questa non piace, perchè ha una select nel `from`
select avg(NumStudenti)
from (
    select Citta, count(*) as NumStudenti
    from Studente
    group by Citta
) as CittaCnt;

-- VISTA RICORSIVA
with recursive Raggiungibile(Orig, Dest, Costo) as (
    select Orig, Dest, Costo
    from Volo where Orig = `Milano`
    union
    select R.Orig, V.Dest, V.Costo + R.Costo
    from Raggiungibile R
    join Volo V on R.Dest = V.Orig
    where V.Dest not in (
        select Dest from Raggiungibile
    )
);

-- CHECK OPTION
-- posso aggiornare una vista senza rompere nulla?
-- `local`: controlla sulla vista in cui è invocato
-- `cascaded`: controlla sul tutte le viste coinvolte
-- create view `Name` `...` with <cascaded | local> check option;
create view Excellent as
    select distinct S.Matr, Nome, Cognome from Studente S
    join Esame E on S.Matr = E.Matr
    where Voto >= 30
with cascaded check option;
-- sogna che funzioni...

/*  _____ ___    _   _  _ ___   _   ___ _____ ___ ___  _  _
 * |_   _| _ \  /_\ | \| / __| /_\ / __|_   _|_ _/ _ \| \| |
 *   | | |   / / _ \| .` \__ \/ _ \ (__  | |  | | (_) | .` |
 *   |_| |_|_\/_/ \_\_|\_|___/_/ \_\___| |_| |___\___/|_|\_|
 */
-- sono unità di esecuzione incapsulate
    start transaction;
--  `...`
    commit;
    -- end transaction;    -- a mySQL non piace
    start transaction;
--  `...`
    rollback;
-- al cui interno si esegue un comando tra `commit work;` e `rollback work;`
-- in mySQL non funziona nulla
-- begin transaction;
-- update Studente set Matr = Matr - 1;
-- if Matr < 0 then rollback work;
-- else commit work;
-- commit work;
-- end transaction;
-- PROPRIETÀ:
-- - Atomicità (undo e redo senza problemi)
-- - Consistenza (rispetta i vincoli di integrità)
-- - Isolamento (Gli istati intermedi non sono visibili fuori dalla `transaction`
--               evitando un domino di rollback)
-- - Persistenza (Commit mai persi)

/*    _   ___ ___ ___ ___ ___ 
 *   /_\ / __/ __| __/ __/ __|
 *  / _ \ (_| (__| _|\__ \__ \
 * /_/ \_\___\___|___|___/___/
 */
-- il proprietario (creatore) può assegnare privilegi ad altri utenti                           
-- i PRIVILEGI sono composti da:
-- - risorsa
-- - utente che condivide
-- - utente che riceve
-- - azione consentita:
--     - INSERT
--     - UPDATE
--     - DELETE
--     - SELECT
--     - REFERENCES
--     - USAGE
--    (- ALL PRIVILEGES)
-- - possiblità di passare il privilegio

-- grant <`priv1` `, ...`|all privileges> 
-- on `risorsa` 
-- to `utenti` [with grant option]

-- revoke <`priv1` `, ...`|all privileges>  
-- on `risorsa`
-- from `utenti` 
-- [<restrict | cascade>] -- a tutti quelli a cui ha ricevuto il privilegio? No | Si

-- le viste consentono di gestire i privilegi ottimamente

/*  ___ ___  _  _ ___ _____ ___    _   ___ _  _ _____ ___ 
 * / __/ _ \| \| / __|_   _| _ \  /_\ |_ _| \| |_   _/ __|
 *| (_| (_) | .` \__ \ | | |   / / _ \ | || .` | | | \__ \
 * \___\___/|_|\_|___/ |_| |_|_\/_/ \_\___|_|\_| |_| |___/
 */                                                       

-- check(`bool`)
--     dove `bool` è un valore booleano che può dipendere da una qualsiasi query
create table Magazzino (
    CodProd    char(6)     primary key,
    QtaDisp    integer not null
               check(QtaDisp > 0),
    QtaRiord   integer not null,
               check(QtaDisp > 10),
    check(QtaDisp > QtaRiord)
);
-- assertion(`bool`)
create assertion AlmenoUnItem 
check (1 <= (select count(*) from Magazzino))

-- La verifica dei vincoli può essere (non in mySQL che è sempre immediate)
-- IMMEDIATE: la violazione annulla l'ultima modifica
-- DEFERRED:  la violazione annulla l'intera transazione 
--            (la verifica può posticipata appena prima del commit)
-- set constraints deferred
-- `do things`
-- set constraints immediate -- controlla anche i constraints precedenti

/* ___ ___  ___   ___ ___ ___  _   _ ___ ___ 
 *| _ \ _ \/ _ \ / __| __|   \| | | | _ \ __|
 *|  _/   / (_) | (__| _|| |) | |_| |   / _| 
 *|_| |_|_\\___/ \___|___|___/ \___/|_|_\___|
 */                                           

-- DDL: Data Definition   Language
-- DML: Data Manipulation Language (PLSQL)

-- procedure `FuncName` (`args`) is
-- begin
--     Q1, Q2 integer;
--     X      exception; 
--     `query`
--     if Q1 < Q2 then raise(X);
--     `update`
--     if Q1 < Q2 then 
--         `insert`;
-- end;

delimiter //
create procedure insersciPino(x int) 
begin 
    insert into Magazzino (CodProd, QtaDisp, QtaRiord)
        values("pino", 100, 50);
end //
delimiter ;
call insersciPino(3);

-- poi una procedura può essere chiamata
-- `FuncName`(`args`)

/* _____ ___ ___ ___  ___ ___ ___ 
 *|_   _| _ \_ _/ __|/ __| __| _ \
 *  | | |   /| | (_ | (_ | _||   /
 *  |_| |_|_\___\___|\___|___|_|_\
 */
-- Sono delle procedure ma con esecuzione automatica, composti da
-- - EVENTO:     <before | after> <insert | delete | update> [of `attr`] on `table`
-- - CONDIZIONE: [when (`boolean expression`)]
--               <for each row | for each statement>
-- - AZIONE:     `sequenze di istruzioni SQL o PLSQL`

-- Tipologie: 
-- - `for each row`: scatta tupla per tupla
--       variabili: `new`, `old`
-- - `for each statement`: scatta una volta per comando
--       variabili: `new_table`, `old_table`

-- create trigger GestioneRiordino
-- after update of QtaDisp on Magazzino
-- when (new.QtaDisp < new.QtaRiord)
-- for each row
-- X exception
-- begin 
--     if new.QtaDisp < 0 then raise(X);
--     insert into Riordino
--         values(new.CodProd, sysdate, new.QtaRiord)
-- end

-- in mySQL è mooolto diverso
delimiter // -- redefine the ;
create trigger GestioneRiordino
after update on Magazzino
for each row
begin
    if new.QtaDisp < new.QtaRiord then
        insert into Magazzino (CodProd, QtaDisp, QtaRiord)
            values("iuppi", 100, 50);
    end if;
end; //
delimiter ;

-- dai trigger si vorrebbe
-- TERMINAZIONE: no loop infiniti
-- CONFLUENZA:   l'esec termina sempre nello stesso stato
-- IDENTICITÀ di COMPORTAMENTO: per ogni stato e per ogni transazione

-- I `trigger` sono essere usati per implementare l'integrità referenziale:
--     `cascade` e `no action` sono dei trigger

/* _____ ___ ___  ___ 
 *|_   _|_ _| _ \/ __|
 *  | |  | ||  _/\__ \
 *  |_| |___|_|  |___/
 */

-- ORDINE ESECUZIONE: from - where - group by - having (sui gruppi) - select
-- specifica quando prendi decisioni sulla semantica
-- se un nome è ambiguo, si fa riferimento al più vicino (non usare nomi ambigui)
-- `max(count(*))` aggregati di aggregati non esistono
-- gli aggregati possono essere usati senza `group by` se riferiti a tutta la
--     tabella
-- `where count(*)` aggregati nella clausola where (violazione dell'ordine
--      temporale: la `where` viene interpretata prima dell'aggregato)
-- `having max(x)` non è un predicato!
-- `having count(*) = 0` se non c'è il gruppo, è vuoto!
-- `group by` vuole che nella select ci siano solo parametri univoci
--            perciò è suggerito mettere solo aggregati o attributi della 
--            group by nella select
-- `count(x1 = x2)`, count può prendere in ingresso solo
--      `*`, `[disinct] attr`, `all`
-- `count(*)` conta anche i null
-- clausole where contradditorie
-- preferisci il `join` al prodotto cartesiano
-- la select può anche associare delle costanti ai campi, oltre agli attributi
-- le query possono essere inserite anche in una select, purchè restituiscano
--     valori unitari
select sid, ( select count(*)
              from exam
              where sid = S.sid ) as Passed, Name
from student S
group by sid;
-- meglio evitare le query nella clausola from: usa le view
-- DATEDIFF(data1, data2): ritorna la diffenenza il giorni
-- YEAR(data): ritorna l'anno
-- coalesce(a,b,c,d): diventa il primo valore diverso da null tra a,b,c,d
select avg(coalesce(DataResa, Today()) - DataPrestito)
from Prestito;
-- anche se la having è valutata prima della select, si può fare
select sum(grade*credits)/sum(credits) as wgpa
from exam E join course on cid=courseid
group by sid
having wgpa > 24.5;
-- posso imporre che gli attributi debbano essere uguali a coppie
select * from course join mdoa on (year,credits) = (y,c);
-- la query "quanti esami ha dato ogni studente", deve tenere conto anche di
--     coloro che ne hanno dati 0! usa `coalesce` (o `count(examId)`)
--     con un `left join`, o `union`
-- per dire "non compare 2 volte ..."
--     `group by having count(attr) = count(distinct attr)`
--      (usa il left join per comprendere anche coloro che non matchano)
--     `tutti - doppi`
--     dove doppi = util X join util Y on 
--                  (X.id = Y.id and X.data != Y.data)
-- intervalli di tempi sovrapposti:
--     - not (A.end <  B.start or  B.end <  A.start) 
--     -     (A.end >= B.start and B.end >= A.start)
-- `is null`, non usare `= null`
-- `count(distinct attr1, attr2)`
