package esercitazione4.es1_courses;

import esercitazione4.es1_courses.dynamicarray.Course;
import esercitazione4.es1_courses.modules.*;

import java.util.Collection;
import java.util.HashSet;

public class Main {

    public static void main(String[] args) {
        Collection <Person> c1 = new HashSet<>();
		c1.add(new Student("Federico", "Giannini", 10));
        c1.add(new Student("Mario", "Rossi", 10));
        for(Person s : c1) {
            System.out.println(s);
        }
        // Usando un hash set non ha aggiunto Mario Rossi in quanto ha la stessa matricola di Federico Giannini

        System.out.println("\n");
        Lecturer t = new Lecturer("Alessandro", "Margara");
        TeachingAssistant e = new TeachingAssistant("Federico", "Giannini");
        Course c = new Course("Software engineering", t, e);
        c.addLecture("Java", new Date(12, 10, 2021), t);
        c.addStudent(new Student("n1", "s1", 123), 1);
        c.addStudent(new Student("n2", "s2", 123), 2);
        System.out.println("Team 1:");
        c.printStudents(1);
        System.out.println("\nTeam 2:");
        c.printStudents(2);
        System.out.println();
        c.printLectures();
    }
}
