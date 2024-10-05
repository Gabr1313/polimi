package gabr;

public class Corso {
    private final Student[] students;
    private int numStudents;

    public Corso() {
        // array (sta sull'heap)
        // in questo caso e' un puntatore a puntatori (student)
        // Sempre Java di default inizializza a 0 (null) gli studenti
        this.students = new Student[100];
    }

    public void addStudent(Student student) {
        // Student e' final, ma e' un puntatore: 
        // posso cambiare quello a cui punta la memoria
        this.students[numStudents] = student;
        numStudents++;
    }

    public int sum() {
        int sum = 0;
        for (int i = 0; i < numStudents; i++) {
            sum += students[i].getVoto();
        }
        return sum;
    }

    public int sum2() {
        int sum = 0;
        // foreach
        // run-time error perche' non tutti gli studenti sono inizializzati
        for (Student s : students) {
            sum += s.getVoto();
        }
        return sum;
    }
}
