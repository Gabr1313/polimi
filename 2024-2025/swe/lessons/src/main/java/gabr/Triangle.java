package gabr;

public class Triangle extends Polygon implements Printable {
    public Triangle() {
        super(3);
    }

    // metodo obbligatorio perche' Polygon e' abstract
    @Override
    public void draw() {
        System.out.println("Triangle");
    }

    @Override
    public void print() {
        draw();
    }
}
