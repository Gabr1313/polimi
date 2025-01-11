package gabr.pattern.state;

// ReceiveCall and ReceiveMessage should behave differently depending on the state
// Normal -> ring in both cases
// Silent -> ring only for calls
// Night -> never rings
public class NormalPhoneState implements PhoneState {
    @Override
    public void handleCall() {
        System.out.println("Phone rings");
    }

    @Override
    public void handleMessage() {
        System.out.println("Bip Bip");
    }
}
