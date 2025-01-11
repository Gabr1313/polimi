package gabr.pattern.command;

public class CommandRun implements GameCommand {
    public void execute(Game g) {
        g.run();
    }
}
