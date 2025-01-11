package gabr.pattern.observer;

import java.util.ArrayList;
import java.util.List;

public abstract class ClickSource {
    // wow, new syntax
    private final List<ClickObserver> clickObservers = new ArrayList<>();
    // scrivere invece 
    // static {
    //     ....
    // }
    // sono delle operazioni da svolgere quando la classe viene messa in memoria
    // utile tipo a definire i valori di una carta in un gioco usando una hashmap
    // e' circa come fosse un costruttore della classe

    public void addClickObserver(ClickObserver observer) {
        clickObservers.add(observer);
    }

    public void notifyClickObservers() {
        clickObservers.forEach(ClickObserver::onClick);
    }
}
