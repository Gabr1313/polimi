package gabr;

public abstract class Polygon {
    private final int edges;

    public Polygon(int edges) {
        this.edges = edges;
    }

    public int getEdges() {
        return edges;
    }

    // le sottoclassi sono obbligate ad implemente `draw` perche' `Polygon` e' abstract
    public abstract void draw();
}
