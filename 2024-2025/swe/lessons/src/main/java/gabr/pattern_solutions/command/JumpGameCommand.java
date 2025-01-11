package it.polimi.softeng.pattern_solutions.command;

public class JumpGameCommand implements GameCommand {
    @Override
    public void execute(Game game) {
        game.jump();
    }
}
