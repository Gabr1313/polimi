package gabr;

public class Punto3D extends Punto2D {
    private final double z;

    public Punto3D(double x, double y, double z) {
        super(x, y);
        this.z = z;
    }

    @Override
    public double distance(Punto2D other) {
        System.out.println("(3d(2d))");
        return Math.sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + z * z);
    }

    // Overload
    public double distance(Punto3D other) {
        System.out.println("(3d(3d))");
        return Math.sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) +
                (z - other.z) * (z - other.z));
    }
}
