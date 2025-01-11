package gabr.pattern.command;

// We assume all games implement this interface,
// which provides three actions.
public interface Game {
    public void run();

    public void jump();

    public void fire();
}
