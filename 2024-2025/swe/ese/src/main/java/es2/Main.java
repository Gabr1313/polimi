package es2;

public class Main {
    public static void main(String[] args) {
        DayDate d1 = new DayDate(25);

        DayDate d2 = new DayMonthDate(25, 2);
        // DayMonthDate è sottoclasse di di DayDate
        // DayMonthDate ha il costruttore con due parametri interi

        DayMonthDate d3 = new DayMonthDate(20, 4);

        // DayMonthYearDate d4 = new DayMonthDate(25, 2);
        // DayMonthYearDate è sottoclasse di DayMonthDate
        // d4 non può essere inizializzato
        // Stiamo assegnando al tipo statico DayMonthYearDate un DayMonthDate
        // ! ERRORE A COMPILE TIME

        DayMonthYearDate d5 = new DayMonthYearDate(24, 3, 2022);

        Date d6 = new DayDate(24);
        // DayDate è sottoclasse di Date
        // DayDate ha il costruttore con un parametro int

        System.out.println("d1 d2");
        System.out.println(d1.dateDistance(d2));
        // d1 S/D: DayDate
        // d2 S: DayDate, D: DayMonthDate
        // DayDate (tipo statico di d1) ha una versione con parametro
        //      Date e una DayDate
        // Si chiama la versione con parametro DayDate (tipo statico di d2)
        // Il tipo dinamico di d1 coincide con lo statico,
        //      non ci sono override da analizzare
        // Il cast a DayMonthDate nel metodo non dà errore (il tipo dinamico di d2 è DayMonthDate)

        System.out.println("\nd1 d3");
        System.out.println(d1.dateDistance(d3));
        // d1 S/D: DayDate
        // d3 S/D: DayMonthDate
        // DayDate (tipo statico di d1) ha una versione con parametro Date e una DayDate
        // d3 ha tipo statico DayMonthDate:
        //      - questo può essere assegnato al parametro dichiarato DayDate e Date
        //      - il tipo dinamico rimane DayMonthDate
        // Si risale la gerarchia e si scegie la versione con DayDate
        // Il tipo dinamico di d1 coincide con lo statico,
        //      non ci sono override da analizzare
        // Il cast a DayMonthDate nel metodo non dà errore (il tipo dinamico di d3 è DayMonthDate)

        System.out.println("\nd1 d6");
        System.out.println(d1.dateDistance(d6));
        // d1 S/D: DayDate
        // d6 S: Date, D: DayDate
        // DayDate (tipo statico di d1) ha una versione con parametro Date
        //      e una DayDate
        // Si chiama la versione con parametro Date, essendo il tipo statico di d6
        // Il tipo dinamico di d1 coincide con lo statico,
        //      non ci sono override da analizzare
        // Questa fa un cast esplicito a DayDate del parametro,
        //      non dà errore perchè il tipo dinamico è DayDate
        // Si chiama nuovamente dateDistance ma questa volta, dopo il cast,
        //      si utilizza la versione con parametro DayDate
        // Questa nuova versione casta il parametro (S/D DayDate) a DayMonthDate, dà errore
        
        System.out.println("\nd2 d3");
        System.out.println(d2.dateDistance(d3));
        // d2 S: DayDate, D: DayMonthDate
        // d3 S/D: DayMonthDate
        // DayDate (tipo statico di d2) ha una versione
        //      con parametro Date e una DayDate
        // DayMonthDate (tipo dinamico di d2) fa override della versione con Date
        // Si utilizza la versione di  con parametro DayDate, risalendo la gerarchia
        // questa volta il cast a DayMonthDate non dà errore perchè il tipo dinamico del parametro è DayMonthDate

        System.out.println("\nd3 d2");
        System.out.println(d3.dateDistance(d2));
        // d3 S/D: DayMonthDate
        // d2 S: DayDate, D: DayMonthDate
        // DayMonthDate (tipo statico di d3) ha una versione
        //      con parametro Date e una DayMonthDate
        // Eredita da DayDate quella con parametro DayDate.
        // Il tipo dinamico di d3 coincide con lo statico,
        //      non ci sono override da analizzare
        // Si chiama la versione ereditata da DayDate con parametro DayDate (tipo statico di d2)
        // questa volta il cast a DayMonthDate non dà errore perchè il tipo dinamico del parametro è DayMonthDate

        System.out.println("\nd3 d5");
        System.out.println(d3.dateDistance(d5));
        // d3 S/D: DayMonthDate
        // d5 S/D: DayMonthYearDate
        // Si parte dal tipo statico di d3: DayMonthDate
        // Questo ha una versione con parametro Date e una DayMonthDate
        // Eredita da DayDate quello con parametro DayDate
        // Tipo statico e dinamico coincidono, non ci sono override da analizzare.
        // d5 essendo DayMonthYearDate può essere assegnato al parametro DayMonthDate
        //      (la classe immediatamente superiore nella gerarchia)
        // Si chiama la versione di DayMonthDate con parametro DayMonthDate
        // Questa chiama il metodo della superclasse:
        //      - la superclasse di DayMonthDate è DayDate
        //      - p ha tipo statico DayMonthDate, può essere assegnato al parametro
        //      DayDate (classe immediatamente superiore)
        // questa volta il cast a DayMonthDate non dà errore perchè il tipo dinamico del parametro è DayMonthDate

        // System.out.println(d4.dateDistance(d5));
        // ERRORE A COMPILE TIME, d4 non è stata istanziata per errore a compile time.

        System.out.println("\nd5 d3");
        System.out.println(d5.dateDistance(d3));
        // d5 S/D: DayMonthYearDate
        // d3 S/D: DayMonthDate
        // DayMonthYearDate (tipo statico di d5) ha una versione con parametro Date
        //      e una DayMonthYearDate
        // Eredita da DayMonthDate quello con parametro DayMonthDate
        // DayMonthDate a sua volta eredita da DayDate quello con DayDate
        // Il tipo dinamico di d5 coincide con lo statico,
        //      non ci sono override da analizzare
        // Si chiama la versione ereditata da DayMonthDate con parametro DayMonthDate
        // Questa chiama il metodo della superclasse:
        //      - la superclasse di DayMonthDate è DayDate
        //      - p ha tipo statico DayMonthDate, può essere assegnato al
        //      parametro DayDate (classe immediatamente superiore)
        // questa volta il cast a DayMonthDate non dà errore perchè il tipo dinamico del parametro è DayMonthDate

        System.out.println("\nd5 d6");
        System.out.println(d5.dateDistance(d6));
        // d5 S/D: DayMonthYearDate
        // d6 S: Date, D: DayDate
        // DayMonthYearDate (tipo statico di d5) ha una versione con
        //      parametro Date e una DayMonthYearDate
        // Eredita da DayMonthDate quello con parametro DayMonthDate
        // DayMonthDate a sua volta eredita da DayDate quello con DayDate
        // Il tipo dinamico di d5 coincide con lo statico,
        //      non ci sono override da analizzare
        // Si chiama la versione con parametro Date
        // ! ERRORE A RUNTIME NEL CAST DA DayDate (tipo dinamico) a DayMonthYearDate
    }

}
