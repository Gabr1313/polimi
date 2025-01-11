package it.polimi.softeng.pattern_solutions.factory;

import java.util.ArrayList;
import java.util.List;

public class Main {
    // Esempio di uso dei metodi definiti in Student
    // Completare la classe Student implementando un factory method
    public static void main(String[] args) {
        List<Student> studentList = new ArrayList<>();
        studentList.add(new PreparedStudent());
        studentList.add(new LetsTryItAnywayStudent());

        studentList.stream()
                .map(Student::produceExam)
                .forEach(System.out::println);
    }
}

