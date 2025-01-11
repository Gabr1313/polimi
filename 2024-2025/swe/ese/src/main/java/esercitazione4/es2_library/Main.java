package esercitazione4.es2_library;

import esercitazione4.es2_library.modules.Book;
import esercitazione4.es2_library.modules.Library;
import esercitazione4.es2_library.modules.Magazine;
import esercitazione4.es2_library.modules.NewsPaper;

public class Main {
    public static void main(String[] args) {
        Library l = new Library();
        l.addDocument(new Book("Title 1", "Summary 1", "Author 1", l.generateCode(), "Rizzoli"));
        l.addDocument(new Magazine("Title 2", "Summary 2", "Author 2", l.generateCode(), 10));
        l.addDocument(new NewsPaper("Corriere della sera", "Summary 3", "Author 3", l.generateCode(), "2022-09-30"));
        System.out.println(l);

        // Aggiungiamo un magazine con codice 2, l'Hash set non lo aggiunge
        l.addDocument(new Magazine("Title 2", "Summary 2", "Author 2", 2, 10));
        System.out.println("____________");
        System.out.println(l);
        System.out.println("____________");

        // Prestiamo un libro (prestabile)
        l.loanDocument(l.getDocumentByCode(1) );
        System.out.println("____________");
        // Prestiamo un libro già prestato
        l.loanDocument(l.getDocumentByCode(1));
        System.out.println("____________");

        // Prestiamo un magazine (prestabile)
        l.loanDocument(l.getDocumentByCode(2) );
        System.out.println("____________");
        // Prestiamo un magazine già prestato
        l.loanDocument(l.getDocumentByCode(2));
        System.out.println("____________");

        // Prestiamo un giornale (non prestabile)
        l.loanDocument(l.getDocumentByCode(3));
    }
}
