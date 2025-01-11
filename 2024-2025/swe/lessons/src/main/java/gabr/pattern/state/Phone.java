package gabr.pattern.state;

// ReceiveCall and ReceiveMessage should behave differently depending on the state
// Normal -> ring in both cases
// Silent -> ring only for calls
// Night -> never rings
public class Phone {
    private PhoneState s;

    public Phone() {
        this.s = new NormalPhoneState();
    }

    public void receiveCall() {
        s.handleCall();
    }

    public void receiveMessage() {
        s.handleMessage();
    }

    public void setState(PhoneState s) {
        this.s = s;
    }
}
