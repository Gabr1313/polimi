package it.polimi.softeng.pattern_solutions.abstractfactory;

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
