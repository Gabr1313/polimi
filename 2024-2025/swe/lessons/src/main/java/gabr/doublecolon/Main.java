package gabr.doublecolon;

import java.util.LinkedList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Book> l = new LinkedList<Book>();
        // ambigua... ovviamente perche' sono fortissimo
        // l.stream().map(Book::getAuthor).forEach(System.out::println  );
        l.stream().map(x -> x.getAuthor()).forEach(x -> System.out.println(x));
    }
}
