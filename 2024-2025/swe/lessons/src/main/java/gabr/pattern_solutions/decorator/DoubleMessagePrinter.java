package it.polimi.softeng.pattern_solutions.decorator;

public class DoubleMessagePrinter extends MessagePrinter {
    private final MessagePrinter printer;

    public DoubleMessagePrinter(MessagePrinter printer) {
        this.printer = printer;
    }

    @Override
    public void print(String message) {
        printer.print(message + message);
    }
}
