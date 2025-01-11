package gabr.pattern.factory;

public class PreparedStudent extends Student {
    @Override
    public Exam examFactory() {
        return new SufficientExam();
    }
}
