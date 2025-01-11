package it.polimi.softeng.pattern_solutions.factory;

public class LetsTryItAnywayStudent extends Student {
    @Override
    protected Exam examFactory() {
        return new InsufficientExam();
    }
}
