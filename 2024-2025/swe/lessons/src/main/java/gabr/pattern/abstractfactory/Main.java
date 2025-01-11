package gabr.pattern.abstractfactory;

public class Main {
    public static void main(String[] args) {
        // si vuole inizializzare un'interfaccia Dark con una finestra e un menu.
        InterfaceFactory factory = new DarkInterfaceFactory();
        Menu menu = factory.createMenu();
        Window window = factory.createWindow();
        System.out.println(menu + " " + window);
    }
}
