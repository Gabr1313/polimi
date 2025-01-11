package esercitazione4.es3_screen.modules;

import java.util.Collection;

public class Screen {
    private final String separator;

    public Screen(String separator) {
        this.separator = separator;
    }

    public void showContent(Collection<Content> contentCollection) {
        for (Content content : contentCollection) {
            System.out.print(content.textToBePrinted() + separator);
        }
    }
}
