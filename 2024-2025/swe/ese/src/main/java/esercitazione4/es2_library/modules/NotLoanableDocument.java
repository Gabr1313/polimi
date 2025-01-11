package esercitazione4.es2_library.modules;
public abstract class NotLoanableDocument extends Document {
    public NotLoanableDocument(String title, String summary, String author, int code) {
        super(title, summary, author, code);
    }

    public final boolean isLoanable () {return false;}

}
