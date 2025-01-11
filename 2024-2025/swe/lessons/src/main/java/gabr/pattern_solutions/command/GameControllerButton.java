package it.polimi.softeng.pattern_solutions.command;

// TODO implement
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
