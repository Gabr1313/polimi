package gabr.pkg;

public abstract class ComplexAlgo{
    // l'utilizzatore vede solo compute
    public void compute() {
        step1();
        step2();
    }
    // chi eredita devi costrutire questi metodi (implementatore)
    protected abstract void step1();
    protected abstract void step2();
}
