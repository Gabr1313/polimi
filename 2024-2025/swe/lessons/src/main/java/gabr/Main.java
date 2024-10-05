package gabr;

public class Main {
    public static void main(String[] args) { // metodo statico si chiama sulla classe, non sulle
                                             // istanze (che quindi non devono essere istanziate)
        Data d1 = new Data(23, 11, 2003);
        Data d2 = new Data(29, 8, 2003);
        Utils u = new Utils();
        u.swap(d1, d2); // NON swappa ovviamente, non esiste funzione che possa
        System.out.printf("%d %d %d\n", d1.getAnno(), d1.getMese(), d1.getGiorno());
        System.out.printf("%d %d %d\n", d2.getAnno(), d2.getMese(), d2.getGiorno());

        Person p1 = new Person("Nome", 32, StudentType.ING);
        Student s1 = new Student("Studente", 23, StudentType.ING, 10);
        // p2 occupa uno spazion in memoria diverso: il compilatore sa che e' uno
        // studente, e a run-time lo sfrutta
        Person p2 = new Student("Studente2", 24, StudentType.ING, 8); // compila
        // Student s2 = new Person("Nome2", 44); // NON compila
        s1.getVoto();
        // p2.getVoto(); // NON compila
        p1.print();
        p2.print(); // usa quello di Person (a run-time). Funziona perche' e' un Override
                    // `instanceof`, non da usare, serve per capire se Person sia Student o meno

        // un metodo statico lo chiamo sulla classe, non sulle istanze
        System.out.println(Person.getNumPersons());

        Corso cs = new Corso();
        cs.addStudent(s1);
        System.out.println(cs.sum());
        // System.out.print(cs.sum2()); errore, vedi il metodo

        Punto2D q1 = new Punto2D(10, 10);
        Punto3D q2 = new Punto3D(10, 5, 4);
        Punto2D q3 = q2; // modificare q3 modifica anche q2

        // per il chiamante:
        // _ comp-time: tipo statico (le funzioni del tipo dinamico non esistono)
        // ____________ `q2` e' considerato di tipo Punto2D
        // ___run-time: tipo dinamico > tipo statico (le funzioni override, del tipo
        // ____________ dinamico, hanno precedenza)
        // ____________ `q2` e' considerato di tipo Punto3D, e cerca gli Override di
        // ____________ Punto2D (solo gli Override, non anche altre funzioni con
        // ____________ signature diversa...)
        // per il chiamato:
        // _ comp-time: e basta

        // 2d.distance(2d) 3d.distance(2d) 3d.distance(2d)
        System.out.println(q1.distance(q3) + " != " + q3.distance(q1) + " and " + q3.distance(q2));

        // Polygon polipo = new Polygon(3); // error: Polygon is abstact
        Polygon poli1 = new Triangle();
        Polygon poli2 = new Square();
        poli1.draw();
        poli2.draw();
    }

    // un metodo statico puo' chiamare solo metodi statici (`main` puo' `chiamare printtt`)
    public static void printtt(Printable p) {
        p.print();
    }
}
