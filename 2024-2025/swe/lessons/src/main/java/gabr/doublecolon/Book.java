package gabr.doublecolon;

public class Book {
    private String author;
    private String name;

    public Book(String author, String name) {
        this.author = author;
        this.name = name;
    }

    public String getAuthor() {
        return author;
    }

    public static String getAuthor(Book b) {
        return "boooooooooo";
    }

    public String getName() {
        return name;
    }
}
