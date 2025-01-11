package gabr.pattern.state;

public class SilentPhoneState implements PhoneState {
    @Override
    public void handleCall() {
        System.out.println("Phone rings");
    }

    @Override
    public void handleMessage() {
        System.out.println("");
    }
}
