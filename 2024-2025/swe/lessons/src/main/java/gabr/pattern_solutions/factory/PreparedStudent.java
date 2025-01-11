package it.polimi.softeng.pattern_solutions.factory;

public class PreparedStudent extends Student {
    @Override
    protected Exam examFactory() {
        return new SufficientExam();
    }
}
