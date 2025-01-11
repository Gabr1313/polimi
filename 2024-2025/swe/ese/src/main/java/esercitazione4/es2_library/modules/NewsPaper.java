package esercitazione4.es2_library.modules;
public class NewsPaper extends NotLoanableDocument{
    private final String date;

    public NewsPaper(String title, String summary, String author, int code, String date) {
        super(title, summary, author, code);
        this.date = date;
    }

    public String toString () {
        return super.toString() + "\nDate: " + this.date;
    }
}
