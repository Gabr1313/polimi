package gabr.pattern.command;

import java.util.ArrayList;
import java.util.List;

// @todo finish and see solutions
public class GameController {
    private Game game;
    private final List<GameControllerButton> controllerButtons;

    GameController(int numButtons, Game game) {
        this.game = game;
        this.controllerButtons = new ArrayList<>(numButtons);
        for (int i = 0; i < numButtons; i++) {
            controllerButtons.add(new GameControllerButton());
        }
        controllerButtons.forEach(button -> button.setGame(game));
    }

    public void changeGame(Game game) {
        this.game = game;
        controllerButtons.forEach(button -> button.setGame(game));
    }

    public void setButtonCommand(int buttonId, GameCommand command) {
        controllerButtons.get(buttonId).setCommand(command);
    }
}
