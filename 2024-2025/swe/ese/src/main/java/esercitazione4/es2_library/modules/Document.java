package esercitazione4.es2_library.modules;
import java.util.Objects;

public abstract class Document {
    private final String title, summary, author;
    private final int code;

    public Document(String title, String summary, String author, int code) {
        this.title = title;
        this.summary = summary;
        this.author = author;
        this.code = code;
    }

    public int getCode() {
        return code;
    }

    public abstract boolean isLoanable();

    @Override
    public String toString() {
        return "Type: " + this.getClass().getSimpleName() + "\nCode:" + code + "\nTitle: " + title +"\nAuthor: " + author + "\nSummary: " + summary;
    }

    public boolean equals (Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Document d = (Document) o;
        return code == d.code;
    }

    @Override
    public int hashCode() {
        return Objects.hash(code);
    }
}
