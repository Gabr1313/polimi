package it.polimi.softeng.pattern_solutions.adapter;

public class PDFFile implements Printable {
    private final LibPDFFile libPDFFile;

    public PDFFile() {
        this.libPDFFile = new LibPDFFile();
    }

    @Override
    public void print(int size) {
        libPDFFile.stampa(size * 2);
    }
}
