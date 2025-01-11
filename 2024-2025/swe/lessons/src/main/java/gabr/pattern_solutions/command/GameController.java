package it.polimi.softeng.pattern_solutions.command;

import java.util.ArrayList;
import java.util.List;

public class GameController {
    private Game game;
    private final List<GameControllerButton> controllerButtons;

    GameController(int numButtons, Game game) {
        this.game = game;
        this.controllerButtons = new ArrayList<>(numButtons);
        for (int i=0; i<numButtons; i++) {
            controllerButtons.add(new GameControllerButton());
        }
        controllerButtons.forEach(button -> button.setGame(game));
    }

    public void changeGame(Game game) {
        this.game = game;
        controllerButtons.forEach(button -> button.setGame(game));
    }

    // TODO: change signature and add code as needed
    public void setButtonCommand(int buttonId, GameCommand command) {
        controllerButtons.get(buttonId).setCommand(command);
    }

}
