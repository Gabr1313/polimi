package esercitazione4.es3_screen.modules;

public class DoubleContent extends Content {
    public DoubleContent(String text) {
        super(text);
    }

    @Override
    public String textToBePrinted() {
        return super.textToBePrinted() + super.textToBePrinted();
        // text non è accessibile alla sottoclasse in quanto private
    }
}
