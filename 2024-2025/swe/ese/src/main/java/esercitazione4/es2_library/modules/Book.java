package esercitazione4.es2_library.modules;

public class Book extends LoanableDocument {
    private final String publisher;

    public Book (String title, String summary, String author, int code, String publisher){
        super(title, summary, author, code);
        this.publisher = publisher; // attributo specifico della classe Book
    }

    public String getPublisher() {
        return publisher;
    }

    public String toString () {
        return super.toString() + "\nPublisher: " + this.publisher;
    }
}
