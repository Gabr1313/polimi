package gabr.pattern.factory;

public abstract class Student {
    protected abstract Exam examFactory();

    // definire il meotod come final => non ci puo' essere un Ovverride
    public final Exam produceExam() {
        // di solito qui c'e' altro codice, per questo non si usa un semplice 
        // ovveride di produceExam
        Exam ex = examFactory();
        return ex;
    }
}
