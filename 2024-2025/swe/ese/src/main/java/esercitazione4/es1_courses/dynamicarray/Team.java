package esercitazione4.es1_courses.dynamicarray;

import esercitazione4.es1_courses.modules.Mail;
import esercitazione4.es1_courses.modules.Student;

public class Team {
    private final DynamicArrayOfStudents students;

    public Team() {
        students = new DynamicArrayOfStudents();
    }

    public void addStudent(Student s) {
        students.add(s);
    }

    public void sendMail(Mail m) {
        for (int i=0; i< students.size(); i++) {
            students.get(i).receiveMail(m);
        }
    }

    public void printStudents() {
        for (int i=0; i< students.size(); i++) {
            System.out.println(students.get(i));
        }
    }
}
