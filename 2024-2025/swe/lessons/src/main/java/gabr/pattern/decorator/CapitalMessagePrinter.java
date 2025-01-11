package gabr.pattern.decorator;

public class CapitalMessagePrinter extends MessagePrinter {
    private final MessagePrinter p;

    public CapitalMessagePrinter(MessagePrinter p) {
        this.p = p;
    }

    public void print(String message) {
        p.print(message.toUpperCase());
    }
}
