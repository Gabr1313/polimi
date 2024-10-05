package gabr;

public enum StudentType {
    // `enum` e' una alternativa al polimorfismo/ereditarieta': 
    // dipende dai casi cosa sia meglio
    ING("Ingegneria"), // Questa e' un'invocazione del constructor
                       // che altrove si chiama cosi': `StudentType.ING`
    ARCH("Architettura"),
    DES("Design"),
    WRONG("Sorry :(");

    private String name;

    private StudentType(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
