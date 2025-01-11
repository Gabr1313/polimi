
/*
STUDENT ( Sid, Name, Birthdate, City, Sex )

COURSE ( CourseId, Title, Credits, Year, Professor )
  Year is 1 for exams of the 1st year, 2 for exams of the 2nd year, ...

EXAM ( Sid, Cid, Date, Grade )
  Grade is between 18 and 30
*/

-- --------------------------------------------------------------------------------
-- 1. Id of the students who got at least one 30
select distinct Sid
from Exam
where Grade = 30;

-- --------------------------------------------------------------------------------
-- 2. Id, Name and City of origin of the students who got at least one 30
select distinct Sid, Name, City
from Student natural join Exam
where Grade = 30;

-- --------------------------------------------------------------------------------
-- 3. The birthdate of the youngest student
select S.Sid, S.Name, S.Birthdate
from Student S
where S.Birthdate = (
	select max(T.Birthdate)
	from Student T
);

-- --------------------------------------------------------------------------------
-- 4. The GPA of the student with ID = 107
select S.Sid, S.Name, avg(E.Grade) gpa
from Student S natural join Exam E
where S.Sid = 107;

select S.Sid, S.Name, sum(E.Grade * C.Credits) / sum(C.Credits) gpa
from Student S natural join Exam E join Course C on E.Cid = C.CourseId
where S.Sid = 107;

-- --------------------------------------------------------------------------------
-- 5. The GPA of each course
select  C.CourseId, C.Title, avg(E.Grade)
from Course C join Exam E on C.CourseId = E.Cid
group by C.CourseId;

-- --------------------------------------------------------------------------------
-- 6. The number of Credits acquired by each student
select S.Sid, S.Name, coalesce(sum(C.credits),0)
from Student S natural left join Exam E left join Course C on E.Cid = C.CourseId
group by S.Sid;

-- --------------------------------------------------------------------------------
-- 7. The (weighted) GPA of each student
select S.Sid, S.Name, sum(E.Grade * C.Credits) / sum(C.Credits) wgpa
from Student S natural left join Exam E left join Course C on E.Cid = C.CourseId
group by S.Sid;

-- --------------------------------------------------------------------------------
-- 8a. Students who passed at least 2 exams [just the Id]
select E.Sid, count(*)
from Exam E
group by E.Sid
having count(*) >= 2;

-- --------------------------------------------------------------------------------
-- 8b. Students who passed at least 2 exams [also the Name]
select E.Sid, count(*), S.name
from Exam E natural join Student S
group by E.Sid
having count(*) >= 2;

-- --------------------------------------------------------------------------------
-- 9a. Students who passed less than 5 exams [just the Id]
select S.Sid, count(E.cid)
from Exam E natural right join Student S
group by E.Sid
having count(*) < 5;

-- --------------------------------------------------------------------------------
-- 9b. Students who passed less than 5 exams [also the Name]
select S.Sid, count(E.cid), S.name
from Exam E natural right join Student S
group by E.Sid
having count(*) < 5;

-- --------------------------------------------------------------------------------
-- 10a / 10b. Students who passed exactly 4 exams [a. just the Id  b. also the Name]
select E.Sid, count(*), S.name
from Exam E natural join Student S
group by E.Sid
having count(*) = 4;

-- --------------------------------------------------------------------------------
-- 11. For each student, the number of passed exams (including those with 0 exams!)
select S.Sid, count(E.Cid)
from Student S natural left join Exam E
group by S.Sid;

-- --------------------------------------------------------------------------------
-- 12. Students with a GPA that is above 24.5
select S.Sid, S.Name, sum(E.Grade * C.Credits)/sum(C.Credits) gpa
from Student S natural join Exam E join Course C on E.Cid = C.CourseId
group by S.Sid
having sum(E.Grade * C.Credits)/sum(C.Credits) > 24.5;

-- --------------------------------------------------------------------------------
-- 13. The “regular” students, i.e., those with a delta of maximum 3 points
select S.Sid, S.Name, max(E.grade) - min(E.grade) delta
from Student S natural join Exam E
group by S.Sid
having max(E.grade) - min(E.grade) <= 3;

-- --------------------------------------------------------------------------------
-- 14. The (weighted) GPA of each student who passed at least 5 exams
select S.Sid, S.Name, sum(E.Grade * C.Credits)/sum(C.Credits) gpa, count(*) passed
from Student S natural join Exam E join Course C on E.Cid = C.CourseId
group by S.Sid
having count(*) >= 5;

-- --------------------------------------------------------------------------------
-- 15.  The (weighted) GPA for each year of each student who passed at least 5 exams
select S.Sid, S.Name, sum(E.Grade * C.Credits)/sum(C.Credits) gpa, count(*) passed, C.year
from Student S natural join Exam E join Course C on E.Cid = C.CourseId
where S.Sid in (
	select T.Sid
	from Student T natural join Exam F
	group by T.Sid
	having count(*) >= 5
)
group by S.Sid, C.year;

-- --------------------------------------------------------------------------------
-- 16. Students who never got more than 21
select S.Sid, S.Name
from Student S natural left join Exam E
group by S.Sid
having coalesce(max(E.Grade),0) <= 21;

-- --------------------------------------------------------------------------------
-- 17. Id and name of the students who passed exams for a total amount of at least
--     20 credits and never got a grade below 28
select S.Sid, S.Name, min(E.grade), sum(C.credits)
from Student S natural join Exam E join Course C on E.Cid = C.CourseId
group by S.sid
having min(E.grade) >= 28 and sum(C.credits) >= 20;

-- --------------------------------------------------------------------------------
-- 18. Students who got the same grade in two or more exams
select distinct S.Sid, S.Name
from Student S join Exam E on S.Sid = E.sid join Exam F on S.Sid = F.sid
where E.Grade = F.grade and E.Cid <> F.Cid;

-- --------------------------------------------------------------------------------
-- 19. Students who never got the same grade twice
select distinct T.Sid, T.Name
from Student T
where T.sid not in (
	select distinct S.Sid
	from Student S join Exam E on S.Sid = E.sid join Exam F on S.Sid = F.sid
	where E.Grade = F.grade and E.Cid <> F.Cid
);

-- --------------------------------------------------------------------------------
-- 20. Students who always got the very same grade in all their exams
select distinct S.Sid, min(E.grade) grade
from Student S natural join Exam E
group by S.Sid
having min(E.grade) = max(E.grade);

-- --------------------------------------------------------------------------------
-- 21. The name of the youngest student
select S.name, S.birthdate
from Student S
where S.birthdate = (
	select max(T.birthdate)
	from Student T
);

-- --------------------------------------------------------------------------------
-- 22. Students who got all possible different grades
select S.sid, S.name
from Student S natural join Exam E
group by S.sid
having count(distinct E.grade) = 30-18+1;

-- --------------------------------------------------------------------------------
-- 23. Students who never passed any exam
select S.sid, S.name
from Student S natural left join Exam E
where E.grade is null;

-- --------------------------------------------------------------------------------
-- 24. Students who never got an 18
select T.sid, T.name
from Student T
where T.sid not in (
	select distinct E.sid
	from Exam E
	where E.grade = 18
);

-- --------------------------------------------------------------------------------
-- 25. Code and Title of the courses with the minimum number of credits
select C.CourseId, C.Title, C.credits
from Course C
where C.credits in (
	select min(D.credits)
	from Course D
);

-- --------------------------------------------------------------------------------
-- 26. Code and Title of the courses of the first year with minimum number of credits
select C.CourseId, C.Title, C.credits
from Course C
where C.year = 1 and C.credits in (
	select min(D.credits)
	from Course D
	where D.year = 1
);

-- --------------------------------------------------------------------------------
-- 27. Code and Title of the courses with the minimum number of credits of each year
select C.CourseId, C.Title, C.credits, C.year
from Course C
where C.credits in (
	select min(D.credits)
	from Course D
	where C.year = D.year
)
order by C.year;

-- --------------------------------------------------------------------------------
-- 28. Id and Name of the students who passed more exams from the second year than
--     exams from the first year
drop view if exists passedExamPerYear;
create view passedExamPerYear(sid, year, cnt) as
	select T.sid, C.year, count(*) cnt1
	from Student T natural join Exam E join Course C on E.Cid = C.CourseId
	group by T.sid, C.year;

select S.sid, S.name, P.cnt y2, coalesce(Q.cnt, 0) y1
from Student S natural join passedExamPerYear P left join passedExamPerYear Q on S.sid = Q.sid
where P.year = 2 and Q.year = 1 and P.cnt > coalesce(Q.cnt, 0);

-- --------------------------------------------------------------------------------
-- 29. The student(s) with best weighted GPA
drop view if exists allWGPA;
create view allWGPA(sid, wgpa) as 
	select E.sid, sum(E.grade*C.credits)/sum(C.credits)
	from Exam E join Course C on E.cid = C.courseId
	group by E.sid;

select S.sid, S.name, A.wgpa 
from Student S natural join allWGPA A
where A.wgpa = (
	select max(B.wgpa)
	from allWGPA B
);

-- --------------------------------------------------------------------------------
-- 30. The course with the worst GPA
drop view if exists courseGPA;
create view courseGPA(cid, gpa) as
	select E.cid, avg(E.grade)
	from Exam E
	group by E.cid;

select C.courseId, C.Title, D.gpa
from Course C join courseGPA D on C.courseId = D.cid
where D.gpa = (
	select min(E.gpa)
	from courseGPA E
);

-- --------------------------------------------------------------------------------
-- 31. Students with a GPA that is at least 2 points above the overall college GPA
select S.sid, S.name, avg(E.grade)
from Student S natural join Exam E
group by S.sid
having avg(E.grade) - 2 >= (
	select avg(F.grade)
	from Exam F
);

-- --------------------------------------------------------------------------------
-- 32. For each student, their best year in terms of GPA
drop view if exists yearGPA;
create view yearGPA(sid, year, gpa) as
	select E.sid, C.year, avg(E.grade)
	from Exam E join Course C on C.courseId = E.cid
	group by E.sid, C.year;

-- select S.sid, S.name, C.year, avg(E.grade)
-- from Student S natural join Exam E join Course C on C.courseId = E.cid
select S.sid, S.Name, D.gpa, D.year
from Student S natural join yearGPA D
where D.gpa >= all (
	select G.gpa
	from yearGPA G
	where G.sid = D.sid
);

-- --------------------------------------------------------------------------------
-- 33. The most “regular” students, i.e., those with the minimum delta between
--     their worst and best grade
drop view if exists Delta;
create view Delta(sid, delta) as
	select E.sid, max(E.grade) - min(E.grade)
	from Exam E
	group by E.sid;

select S.sid, S.name, D.delta
from Student S natural join Delta D
where D.delta <= all (
	select F.delta
	from Delta F
);

-- --------------------------------------------------------------------------------
-- 34. Students with a weighted GPA that is above the “average weighted GPA”
drop view if exists allWGPA;
create view allWGPA(sid, wgpa) as 
	select E.sid, sum(E.grade*C.credits)/sum(C.credits)
	from Exam E join Course C on E.cid = C.courseId
	group by E.sid;

select S.sid, S.name, A.wgpa
from Student S natural join allWGPA A
where A.wgpa > (
	select avg(B.wgpa)
	from allWGPA B
);

-- --------------------------------------------------------------------------------
-- 35. Students who got all their grades in strictly non-decreasing order over time
--      (i.e., never got a grade worse than a previous one)
select S.sid, S.name
from Student S
where S.sid not in (
	select E.sid
	from Exam E join Exam F on E.sid = F.sid
	where E.Grade < F.Grade and E.date > F.date
);
