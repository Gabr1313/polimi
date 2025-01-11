package gabr.pattern.state;

// ReceiveCall and ReceiveMessage should behave differently depending on the state
// Normal -> ring in both cases
// Silent -> ring only for calls
// Night -> never rings
public interface PhoneState {

    public void handleCall();

    public void handleMessage();
}
