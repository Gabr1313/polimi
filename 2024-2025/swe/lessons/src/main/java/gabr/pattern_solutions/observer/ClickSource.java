package it.polimi.softeng.pattern_solutions.observer;

import java.util.ArrayList;
import java.util.List;

public abstract class ClickSource {
    private final List<ClickObserver> clickObservers = new ArrayList<>();

    public void addClickObserver(ClickObserver observer) {
        clickObservers.add(observer);
    }

    public void notifyClickObservers() {
        clickObservers.forEach(ClickObserver::onClick);
    }

}
