package gabr.pattern.adapter;

public class PdfFile implements Printable {
    private final LibPDFFile f;

    public PdfFile() {
        this.f = new LibPDFFile();
    }

    @Override
    public void print(int size) {
        f.stampa(size * 2);
    }
}
