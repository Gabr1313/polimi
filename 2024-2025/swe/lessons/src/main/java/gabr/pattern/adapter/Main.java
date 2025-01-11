package gabr.pattern.adapter;

public class Main {
    // vorrei stampare un documento pdf Printable usando la libreria LibPDFFile
    public static void main(String[] args) {
        PdfFile f = new PdfFile();
        f.print(1);
    }
}
