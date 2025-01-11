package esercitazione4.es3_screen.modules;

public class TripleContent extends Content {
    public TripleContent(String text) {
        super(text);
    }

    @Override
    public String textToBePrinted() {
        return super.textToBePrinted() + super.textToBePrinted() + super.textToBePrinted();
    }
}
