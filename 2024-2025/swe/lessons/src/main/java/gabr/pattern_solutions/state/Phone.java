package it.polimi.softeng.pattern_solutions.state;

// ReceiveCall and ReceiveMessage should behave differently depending on the state
// Normal -> ring in both cases
// Silent -> ring only for calls
// Night -> never rings
public class Phone {
    private PhoneState state;

    public Phone() {
        this.state = new SilentState();
    }

    public void receiveCall() {
        state.receiveCall();
    }

    public void receiveMessage() {
        state.receiveMessage();
    }

    public void setState(PhoneState state) {
        this.state = state;
    }
}
