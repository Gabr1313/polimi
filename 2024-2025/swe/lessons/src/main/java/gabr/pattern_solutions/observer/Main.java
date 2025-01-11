package it.polimi.softeng.pattern_solutions.observer;

public class Main {
    public static void main(String[] args) {
        LogClickObserver observer = new LogClickObserver();
        UserInterface userInterface = new UserInterface();
        userInterface.addClickObserver(observer);
    }
}
