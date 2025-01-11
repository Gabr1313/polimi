package es1;

class Person {
    protected String name;
    public Person(String name) { this.name = name; }

    public void buy(Device d, double euro) {
        System.out.println("* CLASS PERSON, PARAMETERS (Device, double)");
        System.out.println("d dynamic class: "+ d.getClass().getName());
        System.out.println("euro dynamic class: "+ ((Object)euro).getClass().getName());
        System.out.println(name+" buy "+d+" for "+euro+" euros");
    }
}

class Professor extends Person {
    public Professor(String name) { super(name); }

    public void buy(Device d, int euro) {
        System.out.println("* CLASS PROFESSOR, PARAMETERS (Device, int)");
        System.out.println("d dynamic class: "+ d.getClass().getName());
        System.out.println("euro dynamic class: "+ ((Object)euro).getClass().getName());
        System.out.println("Prof. "+name+" buy "+d+" for exactly "+euro+" euros");
    }
}

class FullProfessor extends Professor {
    public FullProfessor(String name) { super(name); }

    public void buy(Smartwatch d, int euro) {
        System.out.println("* CLASS FULLPROFESSOR, PARAMETERS (Device, int)");
        System.out.println("d dynamic class: "+ d.getClass().getName());
        System.out.println("euro dynamic class: "+ ((Object)euro).getClass().getName());
        System.out.println("Full prof."+name+" buy "+d+" for exactly "+euro+" euros");
    }
}
