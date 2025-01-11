package esercitazione4.es1_courses.modules;

import java.util.ArrayList;
import java.util.Collection;

public class Course {
    private final String name;
    private final Collection<Lecture> lectures;
    private final Team team1;
    private final Team team2;

    public Course(String name) {
        this.name = name;
        lectures = new ArrayList<>();
        this.team1 = new Team();
        this.team2 = new Team();
    }

    public void addLecture(String topic, Date date, Faculty speaker) {
        lectures.add(new Lecture(topic, date, speaker));
    }

    public void addStudent(Student s, int team) {
        teamFromIndex(team).addStudent(s);
    }

    public void printStudents(int team) {
        teamFromIndex(team).printStudents();
    }

    public void printLectures() {
        for (Lecture l : lectures) {
            System.out.println(l);
        }
//        for each
//        Collection ha un metodo che ritorna un Iterator
//        Notare l'uso di generics
//        L'iterator su una collection parte da prima del primo elemento, chiamando next ottengo il primo elemento
//        for (Iterator<Lecture> i = lectures.iterator(); i.hasNext();) {
//            Lecture l = i.next();
//            System.out.println(l);
//        }
    }

    public void sendMail(Mail m, int team) {
        teamFromIndex(team).sendMail(m);
    }

    private Team teamFromIndex(int index) {
        if (index == 1) {
            return team1;
        } else {
            return team2;
        }
    }
}
