package gabr.pattern.abstractfactory;

public class DarkInterfaceFactory extends InterfaceFactory {
    @Override
    public Window createWindow() {
        return new DarkWindow();
    }

    @Override
    public Menu createMenu() {
        return new DarkMenu();
    }
}
