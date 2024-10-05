package gabr;

public class Data {
    private int giorno;
    private int mese;
    private int anno;

    public Data(int giorno, int mese, int anno) {
        this.giorno = giorno;
        this.mese = mese;
        this.anno = anno;
    }

    public Data(int m, int a) {
        this(1, m, a);
    }

    public void capodanno() {
        giorno = 1;
        mese = 1;
        anno++;
    }

    public int getGiorno() {
        return giorno;
    }

    public int getMese() {
        return mese;
    }

    public int getAnno() {
        return anno;
    }
}
