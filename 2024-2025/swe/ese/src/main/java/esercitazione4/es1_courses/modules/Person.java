package esercitazione4.es1_courses.modules;

public abstract class Person {
    // classe astratta, non vogliamo istanziarla
    private final String name;
    private final String surname;

    public Person(String name, String surname) {
        this.name = name;
        this.surname = surname;
    }

    public String getName() {
        return name;
    }

    public String getSurname() {
        return surname;
    }

//    @Override
//    public String toString() {
//        return "Person: " + name + " " + surname;
//    }

    public String toString() {
        return "NOME: " + name + "\nCOGNOME: " + surname;
    }
}
