package gabr.pattern.state;

public class NightPhoneState implements PhoneState {
    @Override
    public void handleCall() {
        System.out.println("");
    }

    @Override
    public void handleMessage() {
        System.out.println("");
    }
}
