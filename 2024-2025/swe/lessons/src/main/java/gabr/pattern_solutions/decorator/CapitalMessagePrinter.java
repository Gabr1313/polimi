package it.polimi.softeng.pattern_solutions.decorator;

public class CapitalMessagePrinter extends MessagePrinter {
    private final MessagePrinter printer;

    public CapitalMessagePrinter(MessagePrinter printer) {
        this.printer = printer;
    }

    @Override
    public void print(String message) {
        printer.print(message.toUpperCase());
    }
}
