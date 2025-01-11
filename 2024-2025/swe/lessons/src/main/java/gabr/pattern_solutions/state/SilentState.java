package it.polimi.softeng.pattern_solutions.state;

public class SilentState implements PhoneState {
    @Override
    public void receiveCall() {
        // Ring
    }

    @Override
    public void receiveMessage() {
        // Silent
    }
}
