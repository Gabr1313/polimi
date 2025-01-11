package gabr.pattern.observer;

public class UserInterface extends ClickSource {
    public void click() {
        this.notifyClickObservers();
    }
}
