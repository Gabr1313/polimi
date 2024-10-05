package gabr;

// implements -> interfaccia che viene implementata
public class Student extends Person implements Printable {
    private final int voto;

    public Student(String name, int age, StudentType s, int voto) {
        super(name, age, s); // `super` mi permette di chiamare un costruttore della sopra-classe
        this.voto = voto;
    }

    public int getVoto() {
        return voto;
    }

    @Override // annotazione (non obbligatoria)
    public void print() {
        System.out.println("Sono " + this.getName() + " e il mio voto e' " + voto);
    }

    // Overload: uso di uno stesso metodo con signature diversa
    public void print(int repetitions) {
        for (int i = 0; i < repetitions; i++) {
            print();
        }
    }
}
