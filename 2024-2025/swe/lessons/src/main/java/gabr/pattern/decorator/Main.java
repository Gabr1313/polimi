package gabr.pattern.decorator;

public class Main {
    public static void main(String[] args) {
        // Vorrei costruire
        // 1. Un DoubleMessagePrinter che stampa il messaggio due volte
        // 2. Un CapitalMessagePrinter che stampa il messaggio tutto maiuscolo
        // Vorrei avere tutte le possibili combinazioni
        // (solo doppio, solo maiuscolo, doppio e maiuscolo, ...)
        MessagePrinter m = new MessagePrinter();
        m.print("Hello");
        m = new DoubleMessagePrinter(m);
        m.print("Hello");
        m = new CapitalMessagePrinter(m);
        m.print("Hello");
        m = new DoubleMessagePrinter(m);
        m.print("Hello");
    }
}
