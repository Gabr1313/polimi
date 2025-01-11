package it.polimi.softeng.pattern_solutions.factory;

public abstract class Student {

    // TODO!
    public final Exam produceExam() {
        // Create exam (depending on the type of student)
        // ... Do something with exam ...
        Exam myExam = examFactory();

        // Return the exam for evaluation
        return myExam;
    }

    protected abstract Exam examFactory();

}
