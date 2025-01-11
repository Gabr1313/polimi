package it.polimi.softeng.pattern_solutions.adapter;

public class Main {
    // TODO: vorrei stampare un documento pdf Printable usando la libreria LibPDFFile
    public static void main(String[] args) {
        PDFFile file = new PDFFile();
        file.print(10);
    }
}
