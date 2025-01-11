-- student(sid, name, birthdate, city, sex)
-- course(courseid, title, credits, year, professor)
-- exam(sid, cid, date, grade)

-- number of credits acquired by each student
select name, sid, sum(credits) crediti, count(*) as numesami
from student natural join exam join course on cid=courseid
group by sid;
-- `natural join` new syntax

-- (?) per considerare anche gli studenti senza crediti presi
select Name, sid, (select coalesce(sum(credits), 0)
                   from exam E join course on cid=courseid
                   where E.sid = S.sid
                  ) as Crediti
from studenta S;

-- GPA
select Name, sid, (select coalesce(sum(credits), 0)
                   from exam E join course on cid=courseid
                   where E.sid = S.sid
                  ) as Crediti,
                  (select avg(grade)
                   from exam E join course on cid=courseid
                   where E.sid = S.sid
                  ) as MediaAritmetica,
                  (select sum(grade*credits)/sum(credits)
                   from exam E join course on cid=courseid
                   where E.sid = S.sid
                  ) as MediaPesata,
from studenta S;

-- studenti che hanno passato almeno 2 esami
-- studenti che hanno passato meno di 5 esami
-- studenti che hanno passato esattamente 4 esami
select sid
from exam
group by sid
having count(*) > 1; -- = 4 -- < 5

-- studenti con GPA > 24.5
select sum(grade*credits)/sum(credits) as wgpa
from exam E join course on cid=courseid
-- where E.sid = S.sid
group by sid
having wgpa > 24.5; -- si puo' fare, seppur la having sia valutata prima delle select!

-- studenti che non hanno voti con piu' di 3 punti di differenza
select sid, max(grade), min(grade), max(grade) - min(grade) as delta,
    sum(grade*credits)/sum(credits) as wgpa
from exam E join course on cid=courseid
group by sid
having max(grade) - min(grade) <= 3;

-- GPA di studenti che hanno passato almeno 5 esami
select sid, count(*) as QE, sum(grade*credits)/sum(credits) as wgpa
from exam E join course on cid=courseid
group by sid
having count(*) > 4;

-- GPA di ogni anno di studenti che hanno passato almeno 5 esami in totale
select sid, year, count(*) as QE, sum(grade*credits)/sum(credits) as wgpa
from exam E join course on cid=courseid
where sid in (select sid  -- query indipendente
              from exam
              group by sid
              having count(*) >= 5
             )
group by sid, year;

select sid, year, count(*) as QE, sum(grade*credits)/sum(credits) as wgpa
from exam E join course on cid=courseid
where 5 <= (select count(*) -- query dipendente dall'esterno
            from exam
            where sid = E.sid
           )
group by sid, year;

-- studenti che hanno passato esami per almeno 20 crediti, e mai preso un voto < 28
select sid,min(grade), sum(credits)
from exam E join course on cid=courseid
group by sid
having sum(grade) >= 20 and min(grade) >= 28;

-- 2 volte lo stesso voto
select *
from exam E1 join exam E2 on (E1.sid, E1.grade) = (E2.sid, E2.grade)
where E1.cid <> E2.cid;

select sid
from exam
group by sid
having count(*) > count (distinct grade)
;

select distinct sid
from exam
group by sid, grade
having count(*) >= 2

-- studenti che hanno preso tutti i voti possibili
select distinct sid
from exam
group by sid
having count(distinct grade) = (select count(distinct grade) 
                                from exam) ;

-- codice e titolo dei corsi con il minimo numero di crediti di ogni anno
select cid, title, year, credits
from course
where credits = (select min(credits)
                 from course
                 where year = C.year)
order by year ;

-- senza binding
create view mdoa(y,c) as -- media ogni anno
select year, min(credits)
from course
group by year;

select * 
from course join mdoa on year = y
where credits = c
order by year ;

select * 
from course join mdoa on (year,credits) = (y,c) -- wow, bella sinstassi
order by year;

select * 
from course, mdoa 
where (year,credits) = (y,c)
order by year;

-- senza binding e senza view
select cid, title, year, credits
from course
where (year, credits) in (
    select year, min(credits)
    from course
    group by year
)
;

-- studenti che hanno passato piu' esami del secondo anno che esami del primo
create view passed_exam_per_year(si,ye,num) as
select sid, year, count(*)
from exam join course on cid=courseid
group by sid, year;

select sid, Name, y2.num as Ex_Y2, y1.num as ExY1
from student join passed_exam_per_year y1 on y1.si = sid
             join passed_exam_per_year y2 on y2.si = sid
where y1.ye = 1 and y2.ye = 2
and y1.num < y2.num;

-- @todo RECUPERA GLI ULTIMI 10 MINUTI DELLA LEZIONE DEL 6/11
-- l'idea e' che le view non siano belle in quanto e' facile non accorgersi
-- di edge cases
