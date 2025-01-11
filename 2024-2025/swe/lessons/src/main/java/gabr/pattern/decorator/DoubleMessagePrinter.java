package gabr.pattern.decorator;

public class DoubleMessagePrinter extends MessagePrinter {
    private final MessagePrinter p;

    public DoubleMessagePrinter(MessagePrinter p) {
        this.p = p;
    }

    public void print(String message) {
        p.print(message + " " + message);
    }
}
