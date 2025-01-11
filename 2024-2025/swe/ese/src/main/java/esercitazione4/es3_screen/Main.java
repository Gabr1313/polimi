package esercitazione4.es3_screen;

import esercitazione4.es3_screen.modules.Content;
import esercitazione4.es3_screen.modules.DoubleContent;
import esercitazione4.es3_screen.modules.Screen;
import esercitazione4.es3_screen.modules.TripleContent;

import java.util.ArrayList;
import java.util.Collection;

public class Main {
    public static void main(String[] args) {
        Collection<Content> contentCollection = new ArrayList<>();
        contentCollection.add(new Content("Single"));
        contentCollection.add(new DoubleContent("Double"));
        contentCollection.add(new TripleContent("Triple"));


        Screen s = new Screen("--");
        s.showContent(contentCollection);
    }
}
