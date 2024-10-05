package gabr;

public class Punto2D {
    // `protected` significa che le sottoclassi ci possono acccedere
    // ma purtroppo anche tutto il package
    // (facendo le cose per bene dovrei spostarlo in un package a parte)
    protected final double x;
    protected final double y;

    public Punto2D(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double distance(Punto2D other) {
        System.out.println("(2d(2d))");
        // essendo `other` della stessa classe, 
        // posso accedere direttamente ai suoi attributi
        return Math.sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
}
