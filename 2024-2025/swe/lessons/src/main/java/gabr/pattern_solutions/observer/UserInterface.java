package it.polimi.softeng.pattern_solutions.observer;

public class UserInterface extends ClickSource {

    public void click() {
        this.notifyClickObservers();
    }
}
