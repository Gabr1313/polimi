package esercitazione4.es1_courses.dynamicarray;

import esercitazione4.es1_courses.modules.*;

public class Course {
    private final String name;
    private final DynamicArrayOfLectures lectures;
    private final Lecturer lecturer;
    private final TeachingAssistant teacher;
    private final Team team1;
    private final Team team2;

    public Course(String name, Lecturer l, TeachingAssistant t) {
        this.name = name;
        lectures = new DynamicArrayOfLectures();
        this.team1 = new Team();
        this.team2 = new Team();
        this.lecturer = l;
        this.teacher = t;
    }

    public void addLecture(String topic, Date date, Faculty speaker) {
        lectures.add(new Lecture(topic, date, speaker));
    }

    public void addLecture(Lecture l) {
        lectures.add(l);
    }

    public void addStudent(Student s, int team) {
        teamFromIndex(team).addStudent(s);
    }

    public void printStudents(int team) {
        teamFromIndex(team).printStudents();
    }

    public void printLectures() {
        for (int i=0; i< lectures.size(); i++) {
            System.out.println(lectures.get(i));
        }
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
