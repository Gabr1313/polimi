package gabr;

public class Person {
    private static int numPersons = 0;
    private final String name; // `final`: il valore assegnato e' immutabile, 
                               // e deve essere settato nel constructor
    private final int age;
    private final StudentType type;

    public Person(String name, int age, StudentType s) {
        this.name = name;
        this.age = age;
        this.type = s;
        numPersons++;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public void print() {
        System.out.println("Sono " + name);
    }

    public static int getNumPersons() {
        return numPersons;
    }

    public int getInterest() {
        // `switch` has to use all the alternatives, compiler error otherwise
        switch (type) {
            case ING -> {
                return 100;
            }
            case ARCH -> {
                return 50;
            }
            default -> { // `default` keyword
                return 0;
            }
        }
    }
}
