package esercitazione4.es1_courses.modules;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;

public class Team {
    private final Collection<Student> students;

    public Team() {
        students = new HashSet<>();
        // per evitare che lo stesso studente sia presente due volte.
        // si basa su hashCode: se esiste già un elemento con lo stesso hashCode non lo aggiunge.
        // si utilizza la diamond notation, non serve indicare il tipo anche quando si istanzia
        // HashSet evita che ci siano elementi uguali
        // Organizza gli elementi in bucket utilizzando il metodo hashCode
        // hashCode è una funzione di hash: restituisce il numero del bucket dati i valori degli attributi selezionati
        // Prima di inserire un elemento controlla che in quel bucket non ci siano altri elementi uguali
        // Per la scelta del bucket utilizza hashCode
        // Per il check sull'uguaglianza utilizza il metodo equals
    }

    public void addStudent(Student s) {
        students.add(s);
    }

    public void sendMail(Mail m) {
        for (Student s : students) {
            s.receiveMail(m);
        }
    }

    public void printStudents() {
        for (Student s : students) {
            System.out.println(s);
        }
    }
}
