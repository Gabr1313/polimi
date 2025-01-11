package esercitazione4.es1_courses.modules;

import java.util.Objects;

public class Student extends Person {
    private final int matricola;

    public Student(String name, String surname, int matricola) {
        super(name, surname);
        // name e surname sono private: non posso accederci direttamente dalla sottoclasse
        // se non chiamiamo il costruttore della superclasse viene chiamato in automatico il costruttore di default
        // se non esiste il costruttore di default il compilatore dà errore
        this.matricola = matricola;
    }

    public int getMatricola() {
        return matricola;
    }

    public void receiveMail(Mail m) {
        System.out.println("Received mail");
        System.out.println(m);
    }

//    @Override
//    public String toString() {
//        return "Student: " + getName() + " " + getSurname() + " " + matricola;
//    }

    public String toString () {
        return "MATRICOLA: " + matricola + "\n" + super.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;
        // a questo punto siamo sicuri che o sarà uno Student o eventualmente una sottoclasse
        Student student = (Student) o;
        return this.matricola == student.matricola;
        // matricola è final. È sempre bene implementare equals su attributi final.
    }

    @Override
    public int hashCode() {
        return Objects.hash(matricola);
    }
}
