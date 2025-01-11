package gabr.pattern.factory;

public class LetsTryItAnywayStudent extends Student {
    @Override
    public Exam examFactory() {
        return new InsufficientExam();
    }
}
