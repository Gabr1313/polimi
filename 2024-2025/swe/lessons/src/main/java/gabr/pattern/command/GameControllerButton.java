package gabr.pattern.command;

public class GameControllerButton {
    private GameCommand command;
    private Game game;

    public void setGame(Game game) {
        this.game = game;
    }

    public GameCommand getCommand() {
        return command;
    }

    public void setCommand(GameCommand command) {
        this.command = command;
    }

    public void onClick() {
        if (command != null) {
            command.execute(game);
        }
    }
}
