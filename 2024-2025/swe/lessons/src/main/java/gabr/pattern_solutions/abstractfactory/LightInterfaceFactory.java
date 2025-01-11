package it.polimi.softeng.pattern_solutions.abstractfactory;

public class LightInterfaceFactory extends InterfaceFactory {
    @Override
    public Window createWindow() {
        return new LightWindow();
    }

    @Override
    public Menu createMenu() {
        return new LightMenu();
    }
}